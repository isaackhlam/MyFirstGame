#include "Enemy.hpp"
#include <algorithm>

Enemy::Enemy(sf::RenderWindow& window){
    // Initalize shape
    shape.setSize(sf::Vector2f(rand()%40+20.f, rand()%40+20.f));
    sf::Color color(rand()%255 + 1, rand()%255 + 1, rand()%255 + 1);
    shape.setFillColor(color);   
    shape.setPosition(sf::Vector2f(
        static_cast<float>(std::max(0.f,rand()%window.getSize().x-shape.getGlobalBounds().width)),
        static_cast<float>(-shape.getGlobalBounds().height)
    ));

    // Initialize varible
    type = 0;
    hp = hpMax = 10;
    damage = rand()%3+1;
    points = rand()%10+5;
}

const sf::FloatRect Enemy::getBounds() const{
    return shape.getGlobalBounds();
}

const int Enemy::getDamage() const{
    return damage;
}

const int Enemy::getPoints() const{
    return points;
}

void Enemy::update(){ 
    shape.move(0.f, 2.5f);
}

void Enemy::render(sf::RenderTarget& target){
    target.draw(shape);
}