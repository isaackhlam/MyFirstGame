#ifndef _GAME_
#define _GAME_

#include <iostream>
#include <vector>
#include <ctime>
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
        void updateEnemies();
        void update(sf::Time);
        void renderEnemies();
        void render();
        void run();

    private:
        // Variables
        sf::RenderWindow window;
        sf::Event event;

        // Mouse Position
        sf::Vector2i mousePosWindow;
        sf::Vector2f mousePosView;

        // Game logic
        unsigned points;
        float enemySpawnTimer;
        float enemySpawnTimerMax;
        int maxEnemies;

        // Game objects
        std::vector<sf::RectangleShape> enemies;
        sf::RectangleShape enemy;
        sf::Texture texture;
        sf::Sprite sprite;
};

#endif
