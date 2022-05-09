#include "Player.hpp"
#include "Bullet.hpp"

Player::Player(){
    // Initialize player
    if(!texture.loadFromFile("./content/texture/Jet.png"))
        std::cout << "Error loading from file" << std::endl;
    sprite.setTexture(texture);
    sprite.setPosition(sf::Vector2f(300.f, 800.f));
    sprite.setScale(sf::Vector2f(0.2f, 0.2f));

    // Initialize variable
    Hp = MaxHp = 10;
    xSpeed = ySpeed = 5.f;
    attackCooldownMax = 10.f;
    attackCooldown = attackCooldownMax;
}

const std::vector<Bullet*> Player::getBullets() const{
    return bullets;
}

const unsigned int Player::getMaxHp() const{
    return MaxHp;
}

const unsigned int Player::getHp() const{
    return Hp;
}

const sf::FloatRect Player::getBounds() const{
    return sprite.getGlobalBounds();
}

const bool Player::canAttack(){
    if(attackCooldown >= attackCooldownMax){
        attackCooldown = 0.f;
        return true;
    }
    return false;
}

void Player::updateAttack(){
    if(attackCooldown < attackCooldownMax)
        attackCooldown += 0.5f;
}

void Player::setHp(unsigned int Hp){
    this->Hp = Hp;
}

void Player::loseHp(int value){
    Hp -= value;
    if(Hp < 0) Hp = 0;
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
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && canAttack()){
        bullets.push_back(new Bullet(sprite.getPosition().x+sprite.getGlobalBounds().width/2,sprite.getPosition().y,0.f,-1.f,4.f));
    }
    
}

void Player::removeBullet(int index){
    delete bullets.at(index);
    bullets.erase(bullets.begin()+index);
}

void Player::updateBullets(){
    unsigned counter = 0;
    for(auto* i : bullets){
        i->update();
        
        if(i->getBounds().top + i->getBounds().height < 0.f){
            removeBullet(counter);
            //--counter;
            //std::cout << bullets.size() << "\n";
        }
        ++counter;
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
    updateAttack();
    updateInput();
    updateBullets();
    updateWindowBoundsCollision(target);
}

void Player::renderPlayer(sf::RenderTarget& target){
    target.draw(sprite);
    
}

void Player::renderBullets(sf::RenderTarget& target){
    for(auto* i : bullets)
        i->render(target);
}

void Player::render(sf::RenderTarget& target){
    renderPlayer(target);
    renderBullets(target);
}