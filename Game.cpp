#include "Game.hpp"

Game::Game(){

    // Initialize 
    endGame = false;
    points = 0;
    health = 10;
    enemySpawnTimerMax = 10.f;
    enemySpawnTimer = enemySpawnTimerMax;
    maxEnemies = 10;
    mouseHeld = false;

    // Initialize window
    window.create(sf::VideoMode(720,960), "SFML Window");
    this->window.setFramerateLimit(144);

    // Initialize Fonts
   if(!font.loadFromFile("./content/fonts/BebasNeue-Regular.ttf")) {
        std::cout << "Error loading from file" << std::endl;
    }

    // Initialize Text
    uiText.setFont(font);
    uiText.setCharacterSize(24);
    uiText.setFillColor(sf::Color::White);
    uiText.setString("NONE");

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

void Game::updateText(){
    std::stringstream ss;
    ss << "Points: " << points << "\n"
        << "Health: " << health << "\n";
    uiText.setString(ss.str());
}

void Game::updateEnemies(){

    // Spawn enemies
    if(enemies.size() < maxEnemies){
        if(enemySpawnTimer >= enemySpawnTimerMax){
            spawnEnemy();
            enemySpawnTimer = 0.f;
        }else
            enemySpawnTimer += 1.f;
    }

    // Move enemies
    for(int i=0;i<enemies.size();i++){
        bool deleted = false;
    
        enemies[i].move(0.f, 1.f);

        if(enemies[i].getPosition().y > window.getSize().y){
            enemies.erase(enemies.begin() + i);
            health -= 1;
            std::cout << "Health: " << health << "\n";
        }
            

    }

    // Check click
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        if(mouseHeld == false){
            mouseHeld = true;
            bool deleted = false;
            for(int i=0;i<enemies.size() && deleted == false;i++){
                if(enemies[i].getGlobalBounds().contains(mousePosView)){
                    deleted = true;
                    enemies.erase(enemies.begin() + i);

                    points += 10.f;
                    std::cout << "Points: " << points << "\n";
                }
            }
        }    
    }else
        mouseHeld = false;

}

void Game::update(sf::Time deltaTime){
    processInput();

    if(endGame == false){
        updateMousePosition();
        updateText();
        updateEnemies();
    }

    if(health <= 0)
        endGame = true;
}

void Game::renderText(sf::RenderTarget& target){
    target.draw(uiText);
}

void Game::renderEnemies(sf::RenderTarget& target){
    for(auto &e : enemies){
        target.draw(e);
    }
}

void Game::render() {

    window.clear();

    renderEnemies(window);
    window.draw(sprite);
    renderText(window);

    window.display();
}

void Game::run(){

    sf::Clock clock;

    while(window.isOpen() && !endGame){
        
        processInput();

        update(clock.restart());

        render();
    }
}
