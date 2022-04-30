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
    sf::FloatRect playerBounds = sprite.getGlobalBounds();
    if(playerBounds.left <= 0.f)
        sprite.setPosition(0.f, playerBounds.top);
    else if(playerBounds.left + playerBounds.width >= target.getSize().x)
        sprite.setPosition(target.getSize().x - playerBounds.width, playerBounds.top);
    if(playerBounds.top <= 0.f)
        sprite.setPosition(playerBounds.left, 0.f);
    else if(playerBounds.top + playerBounds.height >= target.getSize().y)
        sprite.setPosition(playerBounds.left, target.getSize().y - playerBounds.height);

}

void Player::update(const sf::RenderTarget& target){
    // Window bounds collision


    updateInput();
    updateWindowBoundsCollision(target);
}

void Player::render(sf::RenderTarget& target){
    target.draw(sprite);
}