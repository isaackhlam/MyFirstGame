#include "Game.hpp"

Game::Game(){

    // Initialize 
    points = 0;
    enemySpawnTimerMax = 10.f;
    enemySpawnTimer = enemySpawnTimerMax;
    maxEnemies = 10;

    // Initialize window
    window.create(sf::VideoMode(720,960), "SFML Window");
    this->window.setFramerateLimit(144);

    // Initialize player
    if(!texture.loadFromFile("./content/texture/Jet.png"))
        std::cout << "Error loading from file" << std::endl;
    sprite.setTexture(texture);
    sprite.setPosition(sf::Vector2f(400.f, 260.f));
    sprite.setScale(sf::Vector2f(0.2f, 0.2f));
    
    // Initialize enemy
    enemy.setSize(sf::Vector2f(50.f, 50.f));
    enemy.setFillColor(sf::Color::Cyan);

}

void Game::spawnEnemy(){
    enemy.setPosition(
        static_cast<float>(rand() % static_cast<int>(window.getSize().x - enemy.getSize().x)),
        0.f
    );

    enemy.setFillColor(sf::Color::Green);
    enemies.push_back(enemy);
}

void Game::processInput(){

    while (window.pollEvent(event)){
        if (event.type == sf::Event::Closed)
            window.close();
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        sprite.move(-0.5, 0);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        sprite.move(0.5, 0);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        sprite.move(0, -0.5);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        sprite.move(0, 0.5);
}

void Game::updateMousePosition(){
    mousePosWindow = sf::Mouse::getPosition(window);
    mousePosView = window.mapPixelToCoords(mousePosWindow);
}

void Game::updateEnemies(){
    if(enemies.size() < maxEnemies){
        if(enemySpawnTimer >= enemySpawnTimerMax){
            spawnEnemy();
            enemySpawnTimer = 0.f;
        }else
            enemySpawnTimer += 1.f;
    }

    for(int i=0;i<enemies.size();i++){
        bool deleted = false;

        enemies[i].move(0.f, 1.f);
        
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            if(enemies[i].getGlobalBounds().contains(mousePosView)){
                deleted = true;

                points += 10.f;
            }
        }

        if(enemies[i].getPosition().y > window.getSize().y){
            deleted = true;
        }

        if(deleted)
            enemies.erase(enemies.begin() + i);
    }
}

void Game::update(sf::Time deltaTime){
    processInput();
    updateMousePosition();
    updateEnemies();
}

void Game::renderEnemies(){
    for(auto &e : enemies){
        window.draw(e);
    }
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
