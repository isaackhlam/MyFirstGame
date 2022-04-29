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
        void update();
        void render(sf::RenderTarget&);

    private:
        sf::Texture texture;
        sf::Sprite sprite;


};

#endif