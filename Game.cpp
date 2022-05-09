#include "Game.hpp"

Game::Game(){

    // Initialize variable
    points = 0;
    enemySpawnTimerMax = 10.f;
    enemySpawnTimer = enemySpawnTimerMax;
    maxEnemies = 20;

    // Initialize Window
    window.create(sf::VideoMode(720,960), "SFML Window");
    window.setFramerateLimit(144);
    window.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width/2-window.getSize().x/2,0.f));

    // Initialize Backgroud
    if(!worldBackgroundTex.loadFromFile("./content/texture/background.jpg"))
        std::cout << "Error loading from file" << std::endl;
    worldBackground.setTexture(worldBackgroundTex);
    worldBackground.setScale(0.3f,0.3f);

    // Initialize Fonts
   if(!font.loadFromFile("./content/fonts/BebasNeue-Regular.ttf")) {
        std::cout << "Error loading from file" << std::endl;
    }

    // Initialize Text
    uiText.setFont(font);
    uiText.setCharacterSize(24);
    uiText.setFillColor(sf::Color::White);
    uiText.setString("NONE");

    gameOverText.setFont(font);
    gameOverText.setCharacterSize(80);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setString("NONE");
    
}

void Game::processInput(){
    while (window.pollEvent(event)){
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.Event::KeyPressed && event.Event::key.code == sf::Keyboard::Escape)
			window.close();
        if (event.Event::KeyPressed && event.Event::key.code == sf::Keyboard::Num0)
            player.setHp(1);
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

    spawnEnemy();

    for(int i=0; i<enemies.size(); i++){
        enemies[i]->update();
        auto playerBullets = player.getBullets();

        // Combat
        for(size_t j = 0; j<playerBullets.size() ; j++){
            if(playerBullets[j]->getBounds().intersects(enemies[i]->getBounds())){
                points += enemies[i]->getPoints();
                playerBullets.erase(playerBullets.begin()+j);
                player.removeBullet(j);
                delete enemies.at(i);
                enemies.erase(enemies.begin()+i);
            }
        }

        // Culling
        if(enemies[i]->getBounds().top > window.getSize().y){
            delete enemies.at(i);
            enemies.erase(enemies.begin() + i);

        }
        // Player
        else if(enemies[i]->getBounds().intersects(player.getBounds())){
            player.loseHp(enemies[i]->getDamage());
            delete enemies.at(i);
            enemies.erase(enemies.begin() + i);
        }
        
    }
        
}

void Game::updateText(){
    std::stringstream ss;
    ss << "Hp: "<< player.getHp() << "/" << player.getMaxHp() << "\n"
        << "Points: " << points << "\n"
        << "WASD: move \n"
        << "Spacebar: shoot\n";
    uiText.setString(ss.str());
}

void Game::update(sf::Time deltaTime){

    if(player.getHp()>0){
        processInput();
        updateEnemyAndCombat();
        player.update(window);
        updateText();
    }

}

void Game::renderWorld(sf::RenderTarget& target){
    target.draw(worldBackground);
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

    renderWorld(window);
    renderText(window);
    renderEnemies(window);
    player.render(window);
    
    if(player.getHp() <= 0){
        window.clear();
        std::stringstream ss;
        ss <<"Game Over!\n"
            << "You get " << points << " points\n";
        gameOverText.setString(ss.str());
        gameOverText.setPosition(window.getSize().x/2-gameOverText.getLocalBounds().width/2,window.getSize().y/2-gameOverText.getLocalBounds().height/2);
        window.draw(gameOverText);
    }
        

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
