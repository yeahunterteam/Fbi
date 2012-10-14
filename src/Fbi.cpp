/*  Copyright (C) 2011 Twl
	(http://www.github.com/twl)

	Project: http://www.github.com/twl/kyra
*/

#include "StdAfx.h"
using namespace boost::asio;
using namespace fbi;
using namespace fbi::irc;

int main(/*int argc, char* argv[]*/)
{
	io_service io;
	ConnectionPointer conn(new connection(io, "irc.rizon.net", 6667, "Kyrax", "Kyrax"));
	conn->run();
	conn->connect();
	io.run();

	cin.get();
	return 0;
}

