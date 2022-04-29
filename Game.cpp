#include "Game.hpp"
/*
Player::Player(){
    if(!texture.loadFromFile("./image/Jet.png"))
        std::cout << "Error loading from file" << std::endl;
    
    sprite.setTexture(texture);
    sprite.setPosition(sf::Vector2f(400.f, 260.f));
    sprite.setScale(sf::Vector2f(0.2f, 0.2f));
}*/



Game::Game(){

    window.create(sf::VideoMode(720,960), "SFML Window");
    this->window.setFramerateLimit(144);

    if(!texture.loadFromFile("./image/Jet.png"))
        std::cout << "Error loading from file" << std::endl;
    
    sprite.setTexture(texture);
    sprite.setPosition(sf::Vector2f(400.f, 260.f));
    sprite.setScale(sf::Vector2f(0.2f, 0.2f));
    
    //this->enemy.setPosition();
    this->enemy.setSize(sf::Vector2f(50.f, 50.f));
    this->enemy.setFillColor(sf::Color::Cyan);
    this->enemy.setOutlineColor(sf::Color::Green);
    this->enemy.setOutlineThickness(1.f);

}

void Game::spawnEnemy(){
    
}

void Game::processInput(){

    sf::Event event;
    while (window.pollEvent(event)){
        if (event.type == sf::Event::Closed)
            window.close();
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        sprite.move(-0.1, 0);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        sprite.move(0.1, 0);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        sprite.move(0, -0.1);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        sprite.move(0, 0.1);
}

void Game::updateMousePosition(){
    this->mousePosWindow = sf::Mouse::getPosition(this->window);
}

void Game::update(sf::Time deltaTime){
    this->processInput();
    this->updateMousePosition();
    //std::cout << "Mouse pos:" << sf::Mouse::getPosition(this->window).x << " " << sf::Mouse::getPosition(this->window).y << "\n";
}
/*
void Game::update(){

}
*/
void Game::render() {

    window.clear();

    window.draw(this->enemy);
    window.draw(sprite);

    window.display();
}

void Game::run(){

    sf::Clock clock;

    while(window.isOpen()){
        
        processInput();

        //update();
        update(clock.restart());

        render();
    }
}