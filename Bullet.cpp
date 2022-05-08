#include "Bullet.hpp"
#include <iostream>

Bullet::Bullet(){

}

const sf::FloatRect Bullet::getBounds() const{
    return shape.getGlobalBounds();
}

Bullet::Bullet(float xPosition, float yPosition, float x, float y, float speed){
    shape.setRadius(7.f);
    shape.setPosition(xPosition,yPosition);
    shape.setFillColor(sf::Color::Red);
    direction.x = x;
    direction.y = y;
    this->speed = speed;
}

void Bullet::update(){
    shape.move(speed * direction);
   // std::cout << "Speed = " << speed << " "
   // << " Direction = " << direction.y << "\n";
}

void Bullet::render(sf::RenderTarget& target){
    target.draw(shape);
}