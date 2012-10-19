/*  Copyright (C) 2011 Twl
	(http://www.github.com/twl)

	Project: http://www.github.com/twl/kyra
*/

#include "../StdAfx.h"
using namespace boost::system;
using boost::asio::ip::tcp;
using namespace fbi::irc::replies;

namespace fbi
{
	namespace irc
	{
		connection::connection(boost::asio::io_service& ios, string ircHost, unsigned short port, string nick, string user) 
			: io_service(ios), resolver(ios), socket(ios), sent_registering_packets(false)
		{
			Log.Notice("Irc", "Irc rész indítása.");
			
			m_irc_host = ircHost;
			m_irc_port = port;
			m_nick = nick;
			m_user = user;
			
			connection_status = status::not_connected;
		}

		void connection::connect()
		{
			/*tcp::resolver::query query(m_irc_host, m_irc_service);
			resolver.async_resolve(query, boost::bind(&connection::handle_resolve, shared_from_this(), boost::asio::placeholders::error
				, boost::asio::placeholders::iterator));*/

			// DNS lookup

			try
			{
				tcp::resolver::query query(m_irc_host, "0");
				tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
				tcp::resolver::iterator end;

				error_code error = boost::asio::error::host_not_found;

				Log.Notice("Irc", "Kapcsolódás a szerverhez.");

				while(error && endpoint_iterator != end)
				{
					tcp::endpoint ep = endpoint_iterator->endpoint();
					cout << ep.address().to_string() << ":" << ep.port() << endl;
					ep.port(m_irc_port);
					socket.close();
					socket.connect(ep, error);
					endpoint_iterator++;
				}

				if(error)
					throw system_error(error);

				flush();
				sending = false;
				connection_status = status::connected;

				Log.Success("Irc", "Kapcsolódás sikeres.");

				addHandler(successful_auth, boost::bind(&connection::handle_registered, shared_from_this(), _1));

				receive();
				
				//io_service.dispatch(on_connect);
			}
			catch(...)
			{
				connection_status = status::not_connected;
				io_service.dispatch(on_disconnect);
				throw;
			}

		}

		void connection::run()
		{
			on_message = boost::bind(&connection::handle_data, shared_from_this(), _1);
		}

		void connection::flush()
		{
			while(out_queue.size() > 0)
				out_queue.pop();
		}

		void connection::finishSending()
		{
			while(sending)
				io_service.run_one();
		}

		void connection::send(int priority, const string& message)
		{
			net_message msg(priority, message);
			out_queue.push(msg);
			send();
		}

		void connection::send()
		{
			if(!sending && out_queue.size() > 0)
			{
				current_message = out_queue.top();
				out_queue.pop();
				boost::asio::async_write(socket, boost::asio::buffer(current_message.message), boost::bind(&connection::send_finished,
					shared_from_this(), boost::asio::placeholders::error));
				sending = true;
			}
		}

		void connection::send_finished(error_code const& ec)
		{
			if(ec)
			{
				disconnect();
				throw system_error(ec);
			}

			sending = false;
			send();

		}

		void connection::receive()
		{
			boost::asio::async_read_until(socket, inc_buffer, "\n", boost::bind(&connection::receive_finished, shared_from_this(), 
				boost::asio::placeholders::error));
		}

		void connection::receive_finished(error_code const& ec)
		{
			if(ec)
			{
				disconnect();
				throw system_error(ec);
			}

			istream is(&inc_buffer);
			getline(is, lastLine);
			receive();
			io_service.dispatch(boost::bind(on_message, lastLine));
		}

		connection::~connection()
		{
			disconnect();
		}

		void connection::disconnect()
		{
			if(connection_status >= status::connected)
			{
				socket.close();
				connection_status = status::not_connected;
				io_service.dispatch(on_disconnect);
				Log.Warning("Irc", "Kapcsolat bontásra került!");
			}
		}

		int connection::status() const
		{
			return connection_status;
		}

		string connection::irc_host() const
		{
			return m_irc_host;
		}

		void connection::irc_host(string ircHost)
		{
			m_irc_host = ircHost;
		}

		void connection::handle_data(string const& data)
		{
			handle_message(data);

			if(!sent_registering_packets)
			{
				string nickmsg = (boost::format("NICK %1%") % m_nick).str();
				string usermsg = (boost::format("USER %1% 8 * :%1%") % m_user).str();

				cout << nickmsg << endl;
				cout << usermsg << endl << endl;

				send(10, nickmsg);
				send(9, usermsg);

				sent_registering_packets = true;
			}

			cout << data << endl;
		}

		void connection::raw_write(string data)
		{
			boost::asio::write(socket, boost::asio::buffer(data));
		}

		void connection::addHandler(string opcode, opcode_handler handler)
		{
			handlers[opcode] = handler;
		}

		void connection::handle_registered(message const& msg)
		{
			// register others
			addHandler(replies::ping, boost::bind(&connection::handle_ping, shared_from_this(), _1));

			// join channels
			msg.connection->send(1, (boost::format("JOIN %1%") % "#schumix2").str());
		}

		void connection::handle_ping(message const& msg)
		{
			string response = (boost::format("PONG :%1%") % msg.args).str();
			cout << response << endl;

			send(10, response);
		}
	
		void connection::handle_message(string info)
		{
			message mess;

			boost::regex firstRegex("^[:](\\S+)\\s(\\S+|\\d+)\\s(\\S+)\\s(\\S+)\\s[:](.+)");
			boost::cmatch match;

			if(boost::regex_search(info.c_str(), match, firstRegex))
			{
				mess.full = info;
				mess.host = match[1];
				mess.hostmask = match[1];
				mess.opcode = match[2];
				mess.nick = match[3];
				mess.user = match[3];
				mess.channel = match[4];
				mess.args = match[5];
			}
			else
			{
				boost::regex PingRegex("^PING\\s[:](.+)");

				if(boost::regex_search(info.c_str(), match, PingRegex))
				{
					string response = (boost::format("PONG :%1%") % match[1]).str();
					send(10, response);
				}

				boost::regex secondRegex("^(\\S+)\\s[:](\\S+)");

				if(boost::regex_search(info.c_str(), match, secondRegex))
				{
					mess.full = info;
					mess.host = m_irc_host;
					mess.hostmask = m_irc_host;
					mess.opcode = match[1];
					mess.args = match[2];
				}
				else
				{
					boost::regex thirdRegex("(:\\S+)\\s(\\S+|\\d+)\\s(\\S+)\\s:(.+)");

					if(boost::regex_search(info.c_str(), match, thirdRegex))
					{
						mess.full = info;
						mess.hostmask = match[1];
						mess.opcode = match[2];
						mess.channel = match[3];
						mess.args = match[4];

						// split hostmask
						uint32 pos = (mess.hostmask.find('!'));
						mess.nick = mess.hostmask.substr(0, pos);
						mess.host = mess.hostmask.substr(pos + 1);

						pos = (mess.host.find('@'));
						mess.user = mess.host.substr(0, pos);
						mess.host = mess.host.substr(pos + 1);
					}
					else
					{
						Log.Error("Irc", "Nem sikerült az irc üzenetet szétvágni!");
						return;
					}
				}

			}

			mess.connection = shared_from_this();

			try
			{
				int opcode = boost::lexical_cast<int>(mess.opcode);
				cout << "opcode: " << opcode << endl;
			}
			catch(boost::bad_lexical_cast&)
			{

			}

			boost::unordered_map<string, opcode_handler>::iterator it = handlers.find(mess.opcode);
			if(it == handlers.end())
			{
				Log.Notice("Irc", boost::format("Ismeretlen opcode kód: %1%") % mess.opcode);
				return;
			}

			(it->second)(mess); // call the handler
		}
	}
}
