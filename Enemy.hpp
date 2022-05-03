#ifndef _ENEMY_
#define _ENEMY_

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class Enemy{
    
    public:
        // Constructor / Destructor
        Enemy(sf::RenderWindow&);
        ~Enemy() = default;

        // Functions
        void update();
        void render(sf::RenderTarget&);

    private:
        // Variable
        sf::RectangleShape shape;

};

#endif