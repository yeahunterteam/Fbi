/*  Copyright (C) 2012 Megax
*/

#ifndef _PTR_WRAPPER
#define _PTR_WRAPPER

namespace fbi
{
	namespace irc
	{
		class connection;

		typedef boost::shared_ptr<connection> ConnectionPointer;

		//#define NULLCON							boost::shared_ptr<connection>()
	}

	namespace network
	{
		class server;
		class Session;

		typedef boost::shared_ptr<server> ServerPointer;
		typedef boost::shared_ptr<Session> SessionPointer;

		//#define NULLSERV							boost::shared_ptr<server>()
		//#define NULLSESS							boost::shared_ptr<Session>()
	}
}

#endif
