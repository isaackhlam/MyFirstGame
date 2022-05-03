#include "Enemy.hpp"

Enemy::Enemy(sf::RenderWindow& window){
    shape.setSize(sf::Vector2f(rand()%100+100.f, rand()%100+100.f));
    sf::Color color(rand()%255 + 1, rand()%255 + 1, rand()%255 + 1);
    shape.setFillColor(color);   
    shape.setPosition(sf::Vector2f(
        static_cast<float>(rand()%window.getSize().x-shape.getGlobalBounds().width),
        static_cast<float>(rand()%window.getSize().x-shape.getGlobalBounds().height)
    ));
}

void Enemy::update(){ 

}

void Enemy::render(sf::RenderTarget& target){
    target.draw(shape);
}