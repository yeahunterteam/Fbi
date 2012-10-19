/*  Copyright (C) 2011 Twl
	(http://www.github.com/twl)

	Project: http://www.github.com/twl/kyra
*/

#ifndef _IRC_MESSAGE
#define _IRC_MESSAGE

namespace fbi
{
	namespace irc
	{
		class connection;

		struct message
		{
			string hostmask;
			string opcode;
			string channel;
			string args;	

			// split from :fbi!fbi@fbi.the.host
			string nick; // fbi
			string user; // fbi
			string host; // fbi.the.host

			string full;
			ConnectionPointer connection;
		};

		struct net_message
		{
			net_message()
			{
				priority = 0;
				message = "";
			}
			
			net_message(int priority, string msg)
			{
				this->priority = priority;
				message = msg + "\r\n";
			}

			int priority;
			string message;

			bool operator <(const net_message& other) const
			{
				return priority < other.priority;
			}
		};
	}
}

#endif
