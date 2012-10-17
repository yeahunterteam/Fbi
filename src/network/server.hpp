/*  Copyright (C) 2011 Twl
	(http://www.github.com/twl)

	Project: http://www.github.com/twl/kyra
*/

#ifndef _NETWORK_CON
#define _NETWORK_CON

namespace fbi
{
	namespace network
	{
		class Session;

		class server : public boost::enable_shared_from_this<server>
		{
		public:
			server(const boost::asio::ip::tcp::endpoint& endpoint);
			server(boost::asio::io_service& ios, const boost::asio::ip::tcp::endpoint& endpoint);
			~server();

			void connect();
			void disconnect();
			void run();

			void handleaccept(boost::shared_ptr<Session> current_session, const boost::system::error_code& error)
			{
				if(!error)
				{
					current_session->Start();
					// hiba megoldása itt!!!
					boost::shared_ptr<Session> new_session(new Session(io_service));
					acceptor.async_accept(new_session->GetSocket(), boost::bind(&server::handleaccept, this, new_session,
						boost::asio::placeholders::error));
				}
			}

		private:
			boost::asio::io_service io_s;
			boost::asio::io_service& io_service;
			boost::asio::ip::tcp::acceptor acceptor;
		};
	}
}

#endif
