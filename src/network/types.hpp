/*
 * types.hpp
 */

#ifndef _TYPES_HPP
#define _TYPES_HPP

namespace fbi
{
	namespace network
	{
		typedef boost::shared_ptr<string> ChatMessage;
		typedef deque<ChatMessage> ChatMessageQueue;
	}
}

#endif
