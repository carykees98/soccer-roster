all: main clean

main: main.cpp menufunctions.o leaguecontainer.o
	g++ -std=c++11 main.cpp menufunctions.o leaguecontainer.o -o soccer-roster

leaguecontainer.o: player.o leaguecontainer.h leaguecontainer.cpp
	g++ -std=c++11 -c leaguecontainer.cpp player.o

menufunctions.o: menufunctions.h menufunctions.cpp
	g++ -std=c++11 -c menufunctions.cpp

player.o: player.h player.cpp
	g++ -std=c++11 -c player.cpp

clean:
	rm player.o
	rm leaguecontainer.o
	rm menufunctions.o