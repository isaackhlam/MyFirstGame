all: compile link

compile:
	g++ -I src/include -c Player.cpp Game.cpp main.cpp
link:
	g++ Player.o Game.o main.o -o main -L src/lib -l sfml-graphics -l sfml-window -l sfml-system