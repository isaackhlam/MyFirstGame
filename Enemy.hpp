#ifndef _ENEMY_
#define _ENEMY_

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class Enemy{
    
    public:
        // Constructor / Destructor
        Enemy(sf::RenderWindow&);
        ~Enemy() = default;

        // Accessor
        const sf::FloatRect getBounds() const;
        const int getDamage() const;
        const int getPoints() const;

        // Functions
        void update();
        void render(sf::RenderTarget&);

    private:
        // Shape
        sf::RectangleShape shape;
        // Variable
        int type;
        int hp;
        int hpMax;
        int damage;
        int points;

};

#endif