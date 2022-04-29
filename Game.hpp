#ifndef _GAME_
#define _GAME_

#include <iostream>
#include <vector>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
using namespace std;

class Game{

    public:
        // Constructors / Destructors
        Game();
        ~Game() = default;

        // Functions
        void spawnEnemy();
        void processInput();
        void updateMousePosition();
        void update(sf::Time);
        void render();
        void run();

    private:
        //
        sf::RenderWindow window;
        sf::Texture texture;
        sf::Sprite sprite;
        std::vector<sf::RectangleShape> enemies;
        sf::RectangleShape enemy;
        sf::Vector2i mousePosWindow;
};

#endif