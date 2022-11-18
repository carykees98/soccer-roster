all: main clean

main: main.cpp MenuFunctions.o PlayerContainer.o
	g++ -std=c++11 main.cpp MenuFunctions.o PlayerContainer.o -o soccer-roster

MenuFunctions.o: MenuFunctions.h MenuFunctions.cpp
	g++ -std=c++11 -c MenuFunctions.cpp

Player.o: Player.h Player.cpp
	g++ -std=c++11 -c Player.cpp

PlayerContainer.o: Player.o PlayerContainer.h PlayerContainer.cpp
	g++ -std=c++11 -c PlayerContainer.cpp Player.o

clean:
	rm Player.o
	rm PlayerContainer.o
	rm MenuFunctions.o