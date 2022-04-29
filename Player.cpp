#include "Player.hpp"

Player::Player(){
    if(!texture.loadFromFile("./content/texture/Jet.png"))
        std::cout << "Error loading from file" << std::endl;
    sprite.setTexture(texture);
    sprite.setPosition(sf::Vector2f(400.f, 260.f));
    sprite.setScale(sf::Vector2f(0.2f, 0.2f));
}

void Player::update(){

}

void Player::render(sf::RenderTarget& target){
    target.draw(sprite);
}