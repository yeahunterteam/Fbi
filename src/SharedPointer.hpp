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

		//#define NULLCON							boost::shared_ptr<Connection>()
	}
}

#endif
