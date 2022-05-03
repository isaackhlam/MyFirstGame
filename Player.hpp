#ifndef _Player_
#define _Player_

#include <iostream>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>


class Player{

    public:
        // Constructor / Destructor
        Player();
        ~Player() = default;

        // Method
        void updateInput();
        void updateWindowBoundsCollision(const sf::RenderTarget&);
        void update(const sf::RenderTarget&);
        void render(sf::RenderTarget&);

    private:
        int xSpeed;
        int ySpeed;
        sf::Texture texture;
        sf::Sprite sprite;


};

#endif