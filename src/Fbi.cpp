/*  Copyright (C) 2011 Twl
	(http://www.github.com/twl)

	Project: http://www.github.com/twl/kyra
*/

#include "StdAfx.h"
using namespace boost::asio;
using namespace fbi;
using namespace fbi::irc;
using namespace fbi::network;
using boost::asio::ip::tcp;
CLog Log;

void _OnSignal(int s)
{
	switch(s)
	{
	case SIGHUP:
		break;
	case SIGINT:
	case SIGTERM:
	case SIGABRT:
		// majd aminek le kell futnia
		main_shutdown_manager.shutdown();
		break;
	}

	signal(s, _OnSignal);
}

void segfault_handler(int c)
{
	Log.Warning("Crash", "Segfault handler elindult...");

	// majd ami lefut

	Log.Notice("Crash", "Program leáll...");
	abort();
}

void _HookSignals()
{
	Log.Notice("Signals", "Hooking signals...");
	signal(SIGINT, _OnSignal);
	signal(SIGTERM, _OnSignal);
	signal(SIGABRT, _OnSignal);
	signal(SIGHUP, _OnSignal);
	signal(SIGUSR1, _OnSignal);

	// crash handler
	signal(SIGSEGV, segfault_handler);
	signal(SIGFPE, segfault_handler);
	signal(SIGILL, segfault_handler);
	signal(SIGBUS, segfault_handler);
}

void _UnhookSignals()
{
	Log.Notice("Signals", "Unhooking signals...");
	signal(SIGINT, 0);
	signal(SIGTERM, 0);
	signal(SIGABRT, 0);
	signal(SIGHUP, 0);
}

int main(/*int argc, char* argv[]*/)
{
	Log.Init(3);
	Log.Color(TBLUE);
	cout << "Fbi verzió: " << Version << endl;
	cout << "A program célja a megadott irc szerverhez/szerverekhez való kapcsolódás." << endl;
	cout << "Továbbá fogadni az adatokat az fbi project másik részétől." << endl;
	cout << "A program leállításához használja a ctrl+c billentyűkombinációt." << endl;
	cout << "================================================================================" << endl << endl; // 80
	Log.Color(TNORMAL);

	Log.Notice("Main", "Program indul...");
	_HookSignals();

	io_service ios;
	ServerPointer s(new server(ios, tcp::endpoint(tcp::v4(), 6009)));
	boost::thread t(boost::bind(&boost::asio::io_service::run, &ios));

	io_service io;
	ConnectionPointer conn(new connection(io, "irc.yeahunter.hu", 6667, "fbi-teszt", "fbi-teszt"));
	conn->run();
	conn->connect();
	boost::thread t2(boost::bind(&boost::asio::io_service::run, &io));

	//cin.get();

	main_shutdown_manager.wait();
	ios.stop();
	io.stop();
	_UnhookSignals();

	return 0;
}
