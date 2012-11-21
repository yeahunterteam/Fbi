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
		class session;
		class ChatParticipant;

		typedef boost::shared_ptr<server> ServerPointer;
		typedef boost::shared_ptr<session> SessionPointer;
		typedef boost::shared_ptr<ChatParticipant> ChatParticipantPtr;

		//#define NULLSERV							boost::shared_ptr<server>()
		//#define NULLSESS							boost::shared_ptr<session>()
	}

	class Signal;
	typedef boost::shared_ptr<Signal> SignalPointer;
}

#endif
