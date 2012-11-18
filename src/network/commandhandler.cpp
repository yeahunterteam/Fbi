/*
 * sender.cpp
 */

#include "../StdAfx.h"
using namespace boost::asio;

namespace fbi
{
	namespace network
	{
		void session::HandleIgnore(const string& command_id, const string& data, string& answer)
		{
		}

		void session::HandleUnknown(const string& command_id, const string& data, string& answer)
		{
			unknown("Ismeretlen parancs!");
		}

		void session::HandleConnect(const string& command_id, const string& data, string& answer)
		{
			authorized_ = true;
			register_timeout_.cancel();
			connection_timeout_.expires_from_now(boost::posix_time::seconds(PingInterval));
			connection_timeout_.async_wait(boost::bind(&session::HandleConnectionTimeout, shared_from_this(),
				boost::asio::placeholders::error));

			success("Sikeres kapcsolódás a szerverhez. Mostantól jöhetnek az adatok.");
		}

		void session::HandleQuit(const string& command_id, const string& data, string& answer)
		{
			Log.Warning("Cliens", "Kilépett a kliens.");
			cleanup();
		}

		void session::HandlePing(const string& command_id, const string& data, string& answer)
		{
			pong(boost::str(boost::format("Sikeresen megjött a ping. Szerver idő: %1%") % UnixTime()));

			if(!ping_sent_)
			{
				connection_timeout_.expires_from_now(boost::posix_time::seconds(PingInterval));
				connection_timeout_.async_wait(boost::bind(&session::HandleConnectionTimeout, shared_from_this(),
					boost::asio::placeholders::error));
			}
		}

		void session::HandlePong(const string& command_id, const string& data, string& answer)
		{
			if(ping_sent_)
			{
				ping_sent_ = false;
				connection_timeout_.expires_from_now(boost::posix_time::seconds(PingInterval));
				connection_timeout_.async_wait(boost::bind(&session::HandleConnectionTimeout, shared_from_this(),
					boost::asio::placeholders::error));
			}
		}

		void session::HandleName(const string& command_id, const string& data, string& answer)
		{
			cliensname = data;
			newname(boost::str(boost::format("Név sikeresen módosítva lett erre: %1%") % cliensname));
		}

		void session::HandleMessage(const string& command_id, const string& data, string& answer)
		{
			// ide amit továbbítok
		}

		void session::HandleChannelList(const string& command_id, const string& data, string& answer)
		{
			cout << data << endl;
			vector<string> split;
			vector<string> channels;
			boost::split(channels, data, boost::is_any_of(","));

			for(int i = 0; i < split.size(); i++)
			{
				string text = split.at(i);
				channels.push_back(text.erase(0, 1));
			}

			split.clear();

			string nick = "fbi-teszt";
			string host = "irc.yeahunter.hu";
			int port = 6667;

			if(channels.size() <= 20)
			{
				string nick0 = nick + "-1";
				ircinfo info;
				info.channelcout = channels.size();
				info.channels = channels;
				info.nick = nick0;
				info.host = host;
				info.port = port;
				info.run(IoServiceMap[nick0]);
				IrcClientMap[nick0] = info;
			}
			else if(channels.size() > 20)
			{
				int clientcout = 0;
				vector<string> ch;

				for(int i = 0; i < channels.size(); i++)
				{
					ch.push_back(channels.at(i));

					if(ch.size() == 20)
					{
						clientcout++;
						string nick0 = boost::str(boost::format("%1%-%2%") % nick % clientcout);

						ircinfo info;
						info.channelcout = ch.size();
						info.channels = ch;
						info.nick = nick0;
						info.host = host;
						info.port = port;
						info.run(IoServiceMap[nick0]);
						IrcClientMap[nick0] = info;
						ch.clear();
						Sleep(20000);
					}
				}

				if(ch.size() > 0)
				{
					clientcout++;
					string nick0 = boost::str(boost::format("%1%-%2%") % nick % clientcout);

					ircinfo info;
					info.channelcout = ch.size();
					info.channels = ch;
					info.nick = nick0;
					info.host = host;
					info.port = port;
					info.run(IoServiceMap[nick0]);
					IrcClientMap[nick0] = info;
					ch.clear();
				}
			}

			channels.clear();
		}

		void session::HandleAddChannel(const string& command_id, const string& data, string& answer)
		{
			// ide amit továbbítok
		}

		void session::HandleRemoveChannel(const string& command_id, const string& data, string& answer)
		{
			// ide amit továbbítok
		}
	}
}
