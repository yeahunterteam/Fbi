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
			cout << "Initializing" << endl;
			boost::shared_ptr<Session> new_session(new Session(io_service));
			acceptor.async_accept(new_session->GetSocket(), boost::bind(&server::handleaccept, this, new_session,
				boost::asio::placeholders::error));
		}

		void server::run()
		{
			//boost::thread t(boost::bind(&boost::asio::io_service::run, &io_service));
		}

		server::~server()
		{
			disconnect();
		}

		void server::disconnect()
		{
			io_service.stop();
		}
	}
}
