#include "Game.h"



void Game::initVariables()
{

	this->window = nullptr;

    this->points = 0;
    this->enemySpawnTimerMax = 100.f;
    this->enemySpawnTimer = this->enemySpawnTimerMax;
    this->maxEnemies = 5;

}

void Game::initWindow()
{

	this->window = new RenderWindow(VideoMode(800, 600), "game");

    this->window->setFramerateLimit(144);
}

void Game::initEnemy()
{
    this->enemy.setPosition(10.f, 10.f);
    this->enemy.setSize(Vector2f(100.f, 100.f));
    this->enemy.setScale(Vector2f(0.5f, 0.5f));
    this->enemy.setFillColor(Color().Cyan);
    this->enemy.setOutlineColor(Color().Red);
    this->enemy.setOutlineThickness(5.f);
    
}




 

Game::Game() {
    
	this->initVariables();
	this->initWindow();
    //this->initEnemy();

}

Game::~Game() {
	delete this->window;
}


//accsessors
const bool Game::running() const
{
	return this->window->isOpen();
}


// Functions




void Game::spwanEnemy()
{
    /*
     
    -set random pos
    -set random color
    -adds enemy to vector

    */

    RectangleShape enemy;


    this->enemy.setPosition(
        static_cast<float> (rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)), 
        0.f
    );
    this->enemy.setSize(Vector2f(50.f, 50.f));

    this->enemy.setFillColor(Color().Green);
    this->enemies.push_back(this->enemy);


}

void Game::pollEvents() {

    while (this->window->pollEvent(this->ev)) {
        switch (this->ev.type) {

        case Event::Closed:
            this->window->close();
            break;

        case Event::KeyPressed:
            if (ev.key.code == Keyboard::Escape || ev.key.code == Keyboard::Q) this->window->close();
            break;
        }
    }
}

void Game::updateMousePos()
{
    this->mousePosWindow = Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateEnemies()
{
    
    if (this->enemies.size() < this->maxEnemies) {

        if (this->enemySpawnTimer >= this->enemySpawnTimerMax) {
            this->spwanEnemy();
            this->enemySpawnTimer = 0.f;
        }
        else {
            this->enemySpawnTimer += 1.f;
        }

    }

     
    // move enemies
    for (int i = 0; i < this->enemies.size();i++) {
        bool deleted = false;

        this->enemies[i].move(0.f, 1.f);

        if (Mouse::isButtonPressed(Mouse::Left)) {
            if (this->enemies[i].getGlobalBounds().contains(this->mousePosView)) {
                deleted = true;
            }
        }

        if (this->enemies[i].getPosition().y > this->window->getSize().y) deleted = true;

        if(deleted) this->enemies.erase(this->enemies.begin() + i);
    }
}

void Game::update()
{
	this->pollEvents();

    this->updateMousePos();

    this->updateEnemies();
}

void Game::renderEnemies()
{
    for (auto& e : this->enemies) this->window->draw(e);
}

void Game::render()
{
    this->window->clear();

    // draw game objects
    this->renderEnemies();
    this->window->display();
}

