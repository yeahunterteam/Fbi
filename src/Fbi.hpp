/*
 * Fbi.hpp
 */

#ifndef _FBI_HPP
#define _FBI_HPP

namespace fbi
{
	static string Version = "0.0.1";
	#define Sleep(x) boost::this_thread::sleep(boost::posix_time::milliseconds(x));
	//#define USleep(x) boost::this_thread::sleep(boost::posix_time::milliseconds(x/1000));
}

#endif
