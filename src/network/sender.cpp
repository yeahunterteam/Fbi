/*
 * sender.cpp
 */

#include "../StdAfx.h"

namespace fbi
{
	namespace network
	{
		void session::success(string msg)
		{
			deliver(boost::str(boost::format("SUCCESS :%1%\n") % msg));
		}

		void session::unknown(string msg)
		{
			deliver(boost::str(boost::format("404 :%1%\n") % msg));
		}

		void session::ping(string msg)
		{
			deliver(boost::str(boost::format("PING :%1%\n") % msg));
		}

		void session::pong(string msg)
		{
			deliver(boost::str(boost::format("PONG :%1%\n") % msg));
		}

		void session::newname(string msg)
		{
			deliver(boost::str(boost::format("NEWNAME :%1%\n") % msg));
		}
	}
}
