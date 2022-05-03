#include "Enemy.hpp"
#include <algorithm>

Enemy::Enemy(sf::RenderWindow& window){
    // Initalize shape
    shape.setSize(sf::Vector2f(rand()%20+20.f, rand()%20+20.f));
    sf::Color color(rand()%255 + 1, rand()%255 + 1, rand()%255 + 1);
    shape.setFillColor(color);   
    shape.setPosition(sf::Vector2f(
        static_cast<float>(std::max(0.f,rand()%window.getSize().x-shape.getGlobalBounds().width)),
        static_cast<float>(std::max(0.f,(rand()%window.getSize().x-shape.getGlobalBounds().height))/10)
    ));
    // Initialize varible
    type    = 0;
    hpMax   = 10;
    hp      = 10;
    damage  = 1;
    points  = 5;
}

const sf::FloatRect Enemy::getBounds() const{
    return shape.getGlobalBounds();
}

void Enemy::update(){ 
    shape.move(0.f, 2.5f);
}

void Enemy::render(sf::RenderTarget& target){
    target.draw(shape);
}