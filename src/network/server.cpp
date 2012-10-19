/*  Copyright (C) 2011 Twl
	(http://www.github.com/twl)

	Project: http://www.github.com/twl/kyra
*/

#include "../StdAfx.h"
using namespace boost::asio;
using namespace boost::system;

namespace fbi
{
	namespace network
	{
		server::server(const tcp::endpoint& endpoint) : io_service(io_s), acceptor(io_s, endpoint)
		{
			server(io_s, endpoint);
		}

		server::server(boost::asio::io_service& ios, const tcp::endpoint& endpoint)
			: io_service(ios), acceptor(io_service, endpoint)
		{
			Log.Notice("Server", "Server indul...");
			SessionPointer new_session(new session(io_service));
			acceptor.async_accept(new_session->GetSocket(), boost::bind(&server::handleaccept, this, new_session,
				boost::asio::placeholders::error));
		}

		void server::run()
		{
			//boost::thread t(boost::bind(&boost::asio::io_service::run, &io_service));
		}

		void server::handleaccept(SessionPointer current_session, const boost::system::error_code& error)
		{
			if(!error)
			{
				current_session->start();
				SessionPointer new_session(new session(io_service));
				acceptor.async_accept(new_session->GetSocket(), boost::bind(&server::handleaccept, this, new_session,
					boost::asio::placeholders::error));
			}
		}

		server::~server()
		{
			disconnect();
		}

		void server::disconnect()
		{
			io_service.stop();
			Log.Warning("Server", "Kapcsolat bontásra került!");
		}
	}
}
