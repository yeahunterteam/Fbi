/*
 * types.hpp
 */

namespace fbi
{
	namespace network
	{
		typedef boost::shared_ptr<string> ChatMessage;
		typedef deque<ChatMessage> ChatMessageQueue;
	}
}
