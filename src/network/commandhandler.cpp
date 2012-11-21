/*
 * sender.cpp
 */

#include "../StdAfx.h"
using namespace boost::asio;
using namespace boost::algorithm;

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
			boost::cmatch match;
			boost::regex Regex("^(.+)\\s[:](.*)");

			if(boost::regex_search(data.c_str(), match, Regex))
			{
				for(boost::unordered_map<string, ircinfo>::iterator it = IrcClientMap.begin(); it != IrcClientMap.end(); ++it)
				{
					if(std::find(it->second.channels.begin(), it->second.channels.end(), match[1].str()) != it->second.channels.end())
					{
						// \n felismerése és szöveg darabolása
						it->second.irc->send(1, boost::str(boost::format("PRIVMSG %1% :%2%") % match[1].str() % match[2].str()));
						break;
					}
				}
			}
		}

		void session::HandleChannelList(const string& command_id, const string& data, string& answer)
		{
			// megírni hogy a port és az irc szerver is a csatornákkal együt jöjjön át

			vector<string> split;
			vector<string> channels;
			boost::split(split, data, boost::is_any_of(","));

			for(int i = 0; i < split.size(); i++)
			{
				string text = split.at(i);
				trim(text);
				channels.push_back(text);
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
						Sleep(20000); // késleltetés az indításhoz. Majd jöhetne konfigból is akár.
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
			// új csatorna hozzáadása oda ahol van üres hely, ha nincs akkor új botot hoz létre
		}

		void session::HandleRemoveChannel(const string& command_id, const string& data, string& answer)
		{
			// csatorna törlése vagy ha azon bot amiből törölve lett teljesen üres lesz csatorna szempontjából akkor álljon le
		}
	}
}
