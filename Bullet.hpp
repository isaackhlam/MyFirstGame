#ifndef _BULLET_
#define _BULLET_

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class Bullet{

    public:
        // Constructor / Destructor
        Bullet();
        Bullet(float,float,float,float,float);
        ~Bullet() = default;

        // Accessor
        const sf::FloatRect getBounds() const;

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