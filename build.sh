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
g++ -finput-charset=UTF-8 -std=c++0x -o fbi -pipe -Wfatal-errors -w src/*.cpp src/irc/*.cpp src/network/*.cpp -lboost_regex -lboost_system -lboost_thread-mt -lpthread -fpermissive
# Csak debug esetén old fel a következő sort előzőt pedig zárold.
#g++ -finput-charset=UTF-8 -std=c++0x -o fbi -pipe -g -Wfatal-errors -w src/*.cpp src/irc/*.cpp src/network/*.cpp -lboost_regex -lboost_system -lboost_thread-mt -lpthread -fpermissive
mv ./fbi ./bin
echo "Forditas befejezodot. Az allomany a bin mappaban talalhato!";
