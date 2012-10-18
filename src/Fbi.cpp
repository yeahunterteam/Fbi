/*  Copyright (C) 2011 Twl
	(http://www.github.com/twl)

	Project: http://www.github.com/twl/kyra
*/

#include "StdAfx.h"
using namespace boost::asio;
using namespace fbi;
using namespace fbi::irc;
using namespace fbi::network;
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

	io_service ioserver;
	boost::asio::ip::tcp::endpoint endpoint = boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 6009);
	boost::shared_ptr<server> serv(new server(ioserver, endpoint));
	ioserver.run();

	/*io_service io;
	ConnectionPointer conn(new connection(io, "irc.rizon.net", 6667, "Kyrax", "Kyrax"));
	conn->run();
	conn->connect();
	io.run();

	cin.get();*/
	return 0;
}
