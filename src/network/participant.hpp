/*
 * participant.hpp
 */

namespace fbi
{
	namespace network
	{
		class ChatParticipant
		{
		public:
			virtual ~ChatParticipant() {}
			virtual void deliver(const ChatMessage& msg) = 0;
		};
	}
}
