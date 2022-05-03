#include "Player.hpp"
#include "Bullet.hpp"

Player::Player(){
    if(!texture.loadFromFile("./content/texture/Jet.png"))
        std::cout << "Error loading from file" << std::endl;
    sprite.setTexture(texture);
    sprite.setPosition(sf::Vector2f(400.f, 260.f));
    sprite.setScale(sf::Vector2f(0.2f, 0.2f));
    xSpeed = ySpeed = 5.f;
}

void Player::updateInput(){
    // Movement
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

    // Shooting
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        bullets.push_back(Bullet(0.f,0.f,0.f));
    }
    
}

void Player::updateBullets(){
    for(auto i : bullets)
        i.update();
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
    updateBullets();
    updateWindowBoundsCollision(target);
}

void Player::renderPlayer(sf::RenderTarget& target){
    target.draw(sprite);
    
}

void Player::renderBullets(sf::RenderTarget& target){
    for(auto i : bullets)
        i.render(target);
}

void Player::render(sf::RenderTarget& target){
    renderPlayer(target);
    renderBullets(target);
}