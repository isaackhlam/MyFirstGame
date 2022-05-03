all: compile link

compile:
	g++ -I src/include -c Bullet.cpp Enemy.cpp Player.cpp Game.cpp main.cpp
link:
	g++ Bullet.o Enemy.o Player.o Game.o main.o -o main -L src/lib -l sfml-graphics -l sfml-window -l sfml-system