#include "Game.hpp"

Game::Game(){

    // Initialize 
    endGame = false;
    points = 0;
    health = 10;
    enemySpawnTimerMax = 10.f;
    enemySpawnTimer = enemySpawnTimerMax;
    maxEnemies = 20;

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
    
}

void Game::processInput(){
    while (window.pollEvent(event)){
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void Game::spawnEnemy(){
    if(enemySpawnTimer < enemySpawnTimerMax)
        enemySpawnTimer += 1.f;
    else{
        if(enemies.size() < maxEnemies){
            enemies.push_back(new Enemy(window));
            enemySpawnTimer = 0.f;
        }
    }
}

void Game::updateEnemyAndCombat(){
    for(int i=0; i<enemies.size(); i++){
        bool enemyRemoved = false;
        enemies[i]->update();
        auto playerBullets = player.getBullets();

        for(size_t j = 0; j<playerBullets.size() ; j++){
            if(playerBullets[j]->getBounds().intersects(enemies[i]->getBounds())){
                playerBullets.erase(playerBullets.begin()+j);
                player.removeBullet(j);
                enemies.erase(enemies.begin()+i);
                enemyRemoved = true;
            }
        }

        if(!enemyRemoved){
            if(enemies[i]->getBounds().top > window.getSize().y){
            delete enemies.at(i);
            enemies.erase(enemies.begin() + i);
            }
        }
        
    }
        
}

void Game::updateText(){
    std::stringstream ss;
    ss << "Points: " << points << "\n"
        << "Health: " << health << "\n"
        << "WASD: move \n"
        << "Spacebar: shoot\n";
    uiText.setString(ss.str());
}

void Game::update(sf::Time deltaTime){

    if(endGame == false){
        processInput();
        spawnEnemy();
        updateEnemyAndCombat();
        player.update(window);
        updateText();
    }

    if(health <= 0)
        endGame = true;
}

void Game::renderText(sf::RenderTarget& target){
    target.draw(uiText);
}

void Game::renderEnemies(sf::RenderTarget& target){
    for(auto* e : enemies){
        e->render(window);
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

    while(window.isOpen()){
        
        processInput();

        update(clock.restart());

        render();
    }
}
