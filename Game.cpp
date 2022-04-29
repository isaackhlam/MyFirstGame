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
    
    // Initialize enemy
    enemy.setSize(sf::Vector2f(100.f, 100.f));
    enemy.setFillColor(sf::Color::Cyan);

}

void Game::spawnEnemy(){

    enemy.setPosition(
        static_cast<float>(rand() % static_cast<int>(window.getSize().x - enemy.getSize().x)),
        0.f
    );

    int type = rand() % 5;

    switch(type){
        case 0:
            enemy.setFillColor(sf::Color::Magenta);
            enemy.setSize(sf::Vector2f(10.f, 10.f));
            break;
        case 1:
            enemy.setFillColor(sf::Color::Blue);
            enemy.setSize(sf::Vector2f(30.f, 30.f));
            break;
        case 2:
            enemy.setFillColor(sf::Color::Cyan);
            enemy.setSize(sf::Vector2f(50.f, 50.f));
            break;
        case 3:
            enemy.setFillColor(sf::Color::Red);
            enemy.setSize(sf::Vector2f(70.f, 70.f));
            break;
        case 4:
            enemy.setFillColor(sf::Color::Green);
            enemy.setSize(sf::Vector2f(100.f, 100.f));
            break;
        default:
            enemy.setFillColor(sf::Color::Yellow);
            enemy.setSize(sf::Vector2f(100.f, 100.f));
            break;
    }

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
                    
                    // Gain points
                    if(enemies[i].getFillColor() == sf::Color::Magenta)
                        points += 10.f;
                    else if(enemies[i].getFillColor() == sf::Color::Blue)
                        points += 7.f;
                    else if(enemies[i].getFillColor() == sf::Color::Cyan)
                        points += 5.f;
                    else if(enemies[i].getFillColor() == sf::Color::Red)
                        points += 3.f;
                    else if(enemies[i].getFillColor() == sf::Color::Green)
                        points += 1.f;

                    std::cout << "Points: " << points << "\n";

                    //Delete the enemy
                    deleted = true;
                    enemies.erase(enemies.begin() + i);
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
    player.render(window);
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
