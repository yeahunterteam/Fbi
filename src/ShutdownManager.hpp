/*
 * shutdown_manager.hpp
 */

#ifndef __SHUTDOWN_MANAGER_HPP
#define __SHUTDOWN_MANAGER_HPP

namespace fbi
{
	class ShutdownManager
	{
	public:
		ShutdownManager(void) : m_shutdown_now(false) {}
		~ShutdownManager() {}

		inline void shutdown(void)
		{
			boost::mutex::scoped_lock shutdown_lock(m_shutdown_mutex);
			m_shutdown_now = true;
			m_shutdown_cond.notify_all();
		}

		inline void wait(void)
		{
			boost::mutex::scoped_lock shutdown_lock(m_shutdown_mutex);

			while(!m_shutdown_now)
				m_shutdown_cond.wait(shutdown_lock);
		}

	private:
		bool m_shutdown_now;
		boost::mutex m_shutdown_mutex;
		boost::condition m_shutdown_cond;
	};

	static ShutdownManager main_shutdown_manager;
}

#endif
