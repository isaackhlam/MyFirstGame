#include "Player.hpp"

Player::Player(){
    if(!texture.loadFromFile("./content/texture/Jet.png"))
        std::cout << "Error loading from file" << std::endl;
    sprite.setTexture(texture);
    sprite.setPosition(sf::Vector2f(400.f, 260.f));
    sprite.setScale(sf::Vector2f(0.2f, 0.2f));
    xSpeed = ySpeed = 5.f;
}

void Player::updateInput(){
    // Keyboard input
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        sprite.move(-xSpeed, 0.f);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        sprite.move(xSpeed, 0.f);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        sprite.move(0.f, -ySpeed);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        sprite.move(0.f, ySpeed);
    }
    
}

void Player::updateWindowBoundsCollision(const sf::RenderTarget& target){
    if(sprite.getGlobalBounds().left <= 0.f)
        sprite.setPosition(0.f, sprite.getGlobalBounds().top);
    if(sprite.getGlobalBounds().left + sprite.getGlobalBounds().width >= target.getSize().x)
        sprite.setPosition(target.getSize().x - sprite.getGlobalBounds().width, sprite.getGlobalBounds().top);
    if(sprite.getGlobalBounds().top <= 0.f)
        sprite.setPosition(sprite.getGlobalBounds().left, 0.f);
    if(sprite.getGlobalBounds().top + sprite.getGlobalBounds().height >= target.getSize().y)
        sprite.setPosition(sprite.getGlobalBounds().left, target.getSize().y - sprite.getGlobalBounds().height);

}

void Player::update(const sf::RenderTarget& target){
    updateInput();
    updateWindowBoundsCollision(target);
}

void Player::render(sf::RenderTarget& target){
    target.draw(sprite);
}