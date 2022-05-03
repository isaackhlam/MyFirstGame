#ifndef _Player_
#define _Player_

#include <iostream>
#include <vector>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Bullet.hpp"


class Player{

    public:
        // Constructor / Destructor
        Player();
        ~Player() = default;

        // Method
        const bool canAttack();
        void updateAttack();
        void updateInput();
        void updateBullets();
        void updateWindowBoundsCollision(const sf::RenderTarget&);
        void update(const sf::RenderTarget&);
        void renderPlayer(sf::RenderTarget&);
        void renderBullets(sf::RenderTarget&);
        void render(sf::RenderTarget&);

    private:
        int xSpeed;
        int ySpeed;
        float attackCooldown;
        float attackCooldownMax;
        sf::Texture texture;
        sf::Sprite sprite;
        std::vector<Bullet*> bullets;


};

#endif