all: compile link

compile:
	g++ -I src/include -c Enemy.cpp Player.cpp Game.cpp main.cpp
link:
	g++ Enemy.o Player.o Game.o main.o -o main -L src/lib -l sfml-graphics -l sfml-window -l sfml-system