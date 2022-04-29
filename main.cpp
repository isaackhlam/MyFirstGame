#include "Game.hpp"

int main()
{
    std::srand(static_cast<unsigned>(time(NULL)));

    Game game;

    game.run();

    return EXIT_SUCCESS;
}