/*  Copyright (C) 2011 Twl
	(http://www.github.com/twl)

	Project: http://www.github.com/twl/kyra
*/

#ifndef _IRC_REPLIES
#define _IRC_REPLIES

namespace fbi
{
	namespace irc
	{
		namespace replies
		{
			static const string successful_auth = "001";
			static const string motd = "372";
			static const string motd_start = "375";
			static const string motd_end = "376";
			static const string notice = "NOTICE";
			static const string privmsg = "PRIVMSG";
			static const string nick = "NICK";
			static const string join = "JOIN";
			static const string leave = "PART";
			static const string quit = "QUIT";

			static const string ping = "PING";
			static const string pong = "PONG";

			static const string kill = "KILL";
			static const string kick = "KICK";
			static const string mode = "MODE";
			static const string reply_404 = "404";
			static const string nick_error = "433";
			static const string channel_ban = "474";
			static const string no_channel_password = "475";
			static const string reply_319 = "319";

			static const string unknown = "002";
			static const string unknown1 = "003";
			static const string unknown2 = "004";
			static const string unknown3 = "005";
			static const string unknown4 = "042";
			static const string unknown5 = "251";
			static const string unknown6 = "252";
			static const string unknown7 = "253";
			static const string unknown8 = "254";
			static const string unknown9 = "255";
			static const string unknown10 = "265";
			static const string unknown11 = "266";
			static const string unknown12 = "332";
			static const string unknown13 = "333";
			static const string unknown14 = "353";
			static const string unknown15 = "366";
			static const string unknown16 = "412";
			static const string unknown17 = "439";
			static const string unknown18 = "462";
			static const string unknown19 = "451";

			static const string whois = "310";
			static const string whois1 = "311";
			static const string whois2 = "312";
			static const string whois3 = "317";
			static const string whois4 = "318";
			static const string whois5 = "338";
			static const string whois6 = "301";
			static const string whois7 = "307";
			static const string whois8 = "671";
			static const string whois9 = "672";
		}
	}
}

#endif
