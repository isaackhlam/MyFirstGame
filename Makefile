all: compile link

compile:
	g++ -I src/include -c Game.cpp main.cpp
link:
	g++ Game.o main.o -o main -L src/lib -l sfml-graphics -l sfml-window -l sfml-system