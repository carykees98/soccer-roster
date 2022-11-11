all: main clean

main: main.cpp UI.o PlayerContainer.o
	g++ -std=c++11 main.cpp UI.o PlayerContainer.o -o soccer-roster

UI.o: UI.h UI.cpp
	g++ -std=c++11 -c UI.cpp

Player.o: Player.h Player.cpp
	g++ -std=c++11 -c Player.cpp

PlayerContainer.o: Player.o PlayerContainer.h PlayerContainer.cpp
	g++ -std=c++11 -c PlayerContainer.cpp Player.o

clean:
	rm Player.o
	rm PlayerContainer.o
	rm UI.o