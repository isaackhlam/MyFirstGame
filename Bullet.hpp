#ifndef _BULLET_
#define _BULLET_

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class Bullet{

    public:
        // Constructor / Destructor
        Bullet();
        Bullet(sf::Vector2f,float,float,float);
        ~Bullet() = default;

        // Function
        void update();
        void render(sf::RenderTarget&);

    private:
        // Variable
        sf::CircleShape shape;
        sf::Vector2f direction;
        float speed;
};

#endif