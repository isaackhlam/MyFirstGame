#include "Bullet.hpp"

Bullet::Bullet(){

}

Bullet::Bullet(sf::Vector2f position, float x, float y, float speed){
    shape.setRadius(5.f);
    shape.setPosition(position);
    direction.x = x;
    direction.y = y;
    this->speed = speed;
}

void Bullet::update(){

    shape.move(speed * direction);
}

void Bullet::render(sf::RenderTarget& target){
    target.draw(shape);
}