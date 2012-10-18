/*  Copyright (C) 2011 Twl
	(http://www.github.com/twl)

	Project: http://www.github.com/twl/kyra
*/

#ifndef _STDAFX_H
#define _STDAFX_H

#pragma once
#pragma warning(disable: 4512) // triggered within Boost.

#if defined(_WIN32)
#include "targetver.h"
#endif

#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <deque>
#include <set>
#include <signal.h>

#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/signal.hpp>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/assert.hpp>
#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/unordered_map.hpp>
#include <boost/regex.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/locks.hpp>
#include <boost/thread/condition.hpp>

#include <boost/cstdint.hpp>

typedef boost::int8_t int8;
typedef boost::int16_t int16;
typedef boost::int32_t int32;
typedef boost::int64_t int64;

typedef boost::uint8_t uint8;
typedef boost::uint16_t uint16;
typedef boost::uint32_t uint32;
typedef boost::uint64_t uint64;

using namespace std;
using std::string;

/* project */
#include "Log.hpp"
extern fbi::CLog Log;
#include "Fbi.hpp"
#include "SharedPointer.hpp"
#include "shutdown_manager.hpp"
#include "irc/irc_replies.hpp"
#include "irc/irc_message.hpp"
#include "irc/irc_connection.hpp"
#include "network/types.hpp"
#include "network/participant.hpp"
#include "network/session.hpp"
#include "network/server.hpp"

#endif
