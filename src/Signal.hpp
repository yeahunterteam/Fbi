/*
 * Signal.hpp
 */

#ifndef _SIGNAL_HPP
#define _SIGNAL_HPP

namespace fbi
{
	class Signal : public boost::enable_shared_from_this<Signal>
	{
	public:
		Signal();
		~Signal();

		void HookSignals();
		void UnhookSignals();
	};
}

#endif
