all: main clean

main: main.cpp player.o menufunctions.o leaguecontainer.o
	g++ -std=c++11 main.cpp player.o leaguecontainer.o menufunctions.o -o soccer-roster

player.o: player.h player.cpp
	g++ -std=c++11 -c player.cpp

leaguecontainer.o:leaguecontainer.h leaguecontainer.cpp
	g++ -std=c++11 -c leaguecontainer.cpp

menufunctions.o: menufunctions.h menufunctions.cpp
	g++ -std=c++11 -c menufunctions.cpp

clean:
	rm player.o
	rm leaguecontainer.o
	rm menufunctions.o