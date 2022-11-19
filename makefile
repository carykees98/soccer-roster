all: main clean

main: main.cpp MenuFunctions.o LeagueContainer.o
	g++ -std=c++11 main.cpp MenuFunctions.o LeagueContainer.o -o soccer-roster

MenuFunctions.o: MenuFunctions.h MenuFunctions.cpp
	g++ -std=c++11 -c MenuFunctions.cpp

Player.o: Player.h Player.cpp
	g++ -std=c++11 -c Player.cpp

LeagueContainer.o: Player.o LeagueContainer.h LeagueContainer.cpp
	g++ -std=c++11 -c LeagueContainer.cpp Player.o

clean:
	rm Player.o
	rm LeagueContainer.o
	rm MenuFunctions.o