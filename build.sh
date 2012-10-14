#!/bin/sh
# Copyright (C) 2010-2012 Megax <http://megax.yeahunter.hu/>
# Auto Builder.

echo "\nFbi Auto Builder by Megax.";
echo "Program segitsegevel konyeden fordithato a kod.\n";
if(ls | grep bin); then
	echo "bin mappa mar letezik\n";
else
	mkdir bin
	echo "bin mappa letrehozva.\n";
fi
g++ -finput-charset=UTF-8 -std=c++0x -o fbi -pipe -Wfatal-errors -w src/*.cpp src/irc/*.cpp -lboost_regex -lboost_system -fpermissive
# Csak debug esetén old fel a következő sort előzőt pedig zárold.
#g++ -finput-charset=UTF-8 -std=c++0x -o schumix -pipe -g -Wfatal-errors -w src/*.cpp src/Rss/*.cpp src/Vezerlo/*.cpp src/DefaultConfig/*.cpp src/Calculator/*.cpp src/IRC/*.cpp src/Commands/*.cpp src/Console/*.cpp src/RemoteAccess/*.cpp src/Shared/Auth/*.cpp src/Shared/Config/*.cpp src/Shared/Database/*.cpp src/Shared/Network/*.cpp src/Shared/Threading/*.cpp -lcrypto -lcurl -lboost_regex -lmysqlclient -lboost_thread -lpthread
mv ./fbi ./bin
echo "Forditas befejezodot. Az allomany a bin mappaban talalhato!";
