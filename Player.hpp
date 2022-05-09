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

        // Accessor
        const std::vector<Bullet*> getBullets() const;
        const unsigned int getMaxHp() const;
        const unsigned int getHp() const;
        const sf::FloatRect getBounds() const;
        

        // Method
        const bool canAttack();
        void updateAttack();
        void setHp(unsigned int);
        void loseHp(int);
        void updateInput();
        void removeBullet(int);
        void updateBullets();
        void updateWindowBoundsCollision(const sf::RenderTarget&);
        void update(const sf::RenderTarget&);
        void renderPlayer(sf::RenderTarget&);
        void renderBullets(sf::RenderTarget&);
        void render(sf::RenderTarget&);

    private:
        unsigned int MaxHp;
        unsigned int Hp;
        int xSpeed;
        int ySpeed;
        float attackCooldown;
        float attackCooldownMax;
        sf::Texture texture;
        sf::Sprite sprite;
        std::vector<Bullet*> bullets;


};

#endif