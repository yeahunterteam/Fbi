/*
 * sender.cpp
 */

#include "../StdAfx.h"

using namespace boost::posix_time;

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
			cliensname = "asd"; // itt majd szedje ki az adatokból.
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
			ptime t(second_clock::local_time());
			pong(boost::str(boost::format("Sikeres megjött a ping. Szerver idő: %1%") % UnixTime()));

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
	}
}
