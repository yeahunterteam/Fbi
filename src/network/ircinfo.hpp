/*  Copyright (C) 2011 Twl
	(http://www.github.com/twl)

	Project: http://www.github.com/twl/kyra
*/

#ifndef _IRC_INFO
#define _IRC_INFO

namespace fbi
{
	namespace network
	{
		using namespace boost::asio;
		using namespace fbi::irc;

		struct ircinfo
		{
		public:
			void run(io_service& io)
			{
				irc = ConnectionPointer(new connection(io, host, port, nick, nick));
				irc->run();
				irc->connect();
				irc->AddChannels(channels);
				boost::thread th(boost::bind(&io_service::run, &io));
			}

			int channelcout;
			vector<string> channels;
			string nick;
			string host;
			int port;
			ConnectionPointer irc;
		};
	}
}

#endif
