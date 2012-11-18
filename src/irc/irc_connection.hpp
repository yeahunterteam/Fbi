/*  Copyright (C) 2011 Twl
	(http://www.github.com/twl)

	Project: http://www.github.com/twl/kyra
*/

#ifndef _IRC_CON
#define _IRC_CON

namespace fbi
{
	namespace irc
	{
		using boost::asio::ip::tcp;

		struct status
		{
			static const int not_connected = 0;
			static const int resolving = 1;
			static const int connected = 2;
			static const int registering = 3;
			static const int registered = 4;
		};

		typedef boost::function<void (message const&)> opcode_handler;

		class connection : public boost::enable_shared_from_this<connection>
		{
		public:
			connection(boost::asio::io_service& ios, string ircHost, unsigned short port, string nick, string user);
			~connection();

			string irc_host() const;
			void irc_host(string);
			int status() const;

			void raw_write(string data);

			void connect();
			void disconnect();
			void finishSending();
			void send(int priority, string const& message);
			void flush();

			void run();

			boost::function<void ()> on_connect;
			boost::function<void (const string&)> on_message;
			boost::function<void ()> on_disconnect;
			
			void addHandler(string opcode, opcode_handler handler);
			void AddChannels(vector<string> ch);

		protected:
			void handle_resolve(boost::system::error_code const&, tcp::resolver::iterator);
			void handle_connect(boost::system::error_code const&);
			void handle_read(boost::system::error_code const&, size_t);

			void handle_data(string const&);

			void handle_message(string);

			void handle_registered(message const&);
			void handle_ping(message const&);

		private:
			void receive();
			void receive_finished(boost::system::error_code const& ec);
			void send();
			void send_finished(boost::system::error_code const& ec);

			boost::asio::io_service& io_service;
			tcp::resolver resolver;
			tcp::socket socket;
			boost::asio::streambuf inc_buffer;

			priority_queue<net_message> out_queue;
			net_message current_message;

			string m_irc_host;
			unsigned short m_irc_port;
			string m_nick;
			string m_user;

			string lastLine;
			bool sending;

			int connection_status;
			bool sent_registering_packets;

			vector<string> channels;
			
			boost::unordered_map<string, opcode_handler> handlers;
		};
	}
}

#endif
