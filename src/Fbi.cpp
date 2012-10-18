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

	io_service ios;
	boost::shared_ptr<server> s(new server(ios, tcp::endpoint(tcp::v4(), 6009)));
	boost::thread t(boost::bind(&boost::asio::io_service::run, &ios));

	cout << "asd" << endl;

	io_service io;
	ConnectionPointer conn(new connection(io, "irc.rizon.net", 6667, "Kyrax", "Kyrax"));
	conn->run();
	conn->connect();
	boost::thread t2(boost::bind(&boost::asio::io_service::run, &io));

	cin.get();

	for(;;)
		Sleep(2000);

	return 0;
}
