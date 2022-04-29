#include "Game.hpp"

Game::Game(){

    window.create(sf::VideoMode(720,960), "SFML Window");
    this->window.setFramerateLimit(144);

    if(!texture.loadFromFile("./content/texture/Jet.png"))
        std::cout << "Error loading from file" << std::endl;
    
    sprite.setTexture(texture);
    sprite.setPosition(sf::Vector2f(400.f, 260.f));
    sprite.setScale(sf::Vector2f(0.2f, 0.2f));
    
    enemy.setSize(sf::Vector2f(50.f, 50.f));
    enemy.setFillColor(sf::Color::Cyan);
    enemy.setOutlineColor(sf::Color::Green);
    enemy.setOutlineThickness(1.f);

}

void Game::spawnEnemy(){

}

void Game::processInput(){

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
    mousePosWindow = sf::Mouse::getPosition(window);
}

void Game::updateEnemies(){

}

void Game::update(sf::Time deltaTime){
    processInput();
    updateMousePosition();
    updateEnemies();
}

void Game::renderEnemies(){
    
}

void Game::render() {

    window.clear();

    renderEnemies();
    window.draw(sprite);

    window.display();
}

void Game::run(){

    sf::Clock clock;

    while(window.isOpen()){
        
        processInput();

        update(clock.restart());

        render();
    }
}
