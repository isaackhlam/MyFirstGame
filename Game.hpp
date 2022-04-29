#ifndef _GAME_
#define _GAME_

#include <vector>
#include <ctime>
#include <sstream>
#include "Player.hpp"

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
        void updateText();
        void updateEnemies();
        void update(sf::Time);

        void renderText(sf::RenderTarget&);
        void renderEnemies(sf::RenderTarget&);
        void render();
        void run();

    private:
        // Variables
        sf::RenderWindow window;
        sf::Event event;

        // Mouse Position
        sf::Vector2i mousePosWindow;
        sf::Vector2f mousePosView;

        // Resources
        sf::Font font;

        // Text
        sf:: Text uiText;

        // Game logic
        bool endGame;
        unsigned points;
        int health;
        float enemySpawnTimer;
        float enemySpawnTimerMax;
        int maxEnemies;
        bool mouseHeld;

        // Game objects
        std::vector<sf::RectangleShape> enemies;
        sf::RectangleShape enemy;
        Player player;
        sf::Texture texture;
        sf::Sprite sprite;
};

#endif
