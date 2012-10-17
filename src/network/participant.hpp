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
			virtual void Deliver(const ChatMessage& msg) = 0;
		};

		typedef boost::shared_ptr<ChatParticipant> ChatParticipantPtr;
	}
}
