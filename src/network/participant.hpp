/*
 * participant.hpp
 */

#ifndef _PARTICIPANT_HPP
#define _PARTICIPANT_HPP

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

#endif
