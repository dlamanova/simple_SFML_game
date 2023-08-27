#include <Game.hpp>

//Private functions

void Game::initVariables()
{
    this->window = nullptr;

    //Game logic
    this->points = 0;
    this->enemySpawnTimerMax = 10.f;
    this->enemySpawnTimer = this->enemySpawnTimerMax;
    this->maxEnemies = 5;
}

void Game::initWindow()
{
    this->videoMode.height = 600;
    this->videoMode.width = 800;

    this->window = new sf::RenderWindow(this->videoMode, "My first game", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);

    this->window->setFramerateLimit(60);
}

void Game::initEnemies()
{
    this->enemy.setPosition(10.f, 10.f);
    this->enemy.setSize(sf::Vector2f(50.f, 50.f));
    this->enemy.setFillColor(sf::Color::Cyan);
    // this->enemy.setOutlineColor(sf::Color::Magenta);
    // this->enemy.setOutlineThickness(1.f);
}

//Constructors / Destrctors
Game::Game()
{
    this->initVariables();
    this->initWindow();
    this->initEnemies();
}

Game::~Game()
{
    delete this->window;
}

//Accessors
const bool Game::running() const
{
    return this->window->isOpen();
}

//Functions

void Game::spawnEnemy()
{
    this->enemy.setPosition(
        static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
        //static_cast<float>(rand() % static_cast<int>(this->window->getSize().y - this->enemy.getSize().y))
        0.f
    );

    this->enemy.setFillColor(sf::Color::Green);

    //Spawn the enemy
    this->enemies.push_back(this->enemy);

    //Remove enemies at end of screen
}
void Game::pollEvents()
{
    //Event polling
    while(this->window->pollEvent(this->ev))
    {
        switch(this->ev.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            if(this->ev.key.code == sf::Keyboard::Escape)
            this->window->close();
            break;
        default:
            break;
        }
    }
}
void Game::updateMousePositions()
{
    /*
        Updates the mouse positions:
        - Mouse position relative to window (Vector2i)
    */
   this->mousePosWindow = sf::Mouse::getPosition(*this->window);
   this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateEnemies()
{
    //Updating the timer for enemy spawning
    if(this->enemies.size() < this->maxEnemies)
    {
        if(this->enemySpawnTimer >= this->enemySpawnTimerMax)
        {
            //Spawn the enemy and reset the timer
            this->spawnEnemy();
            this->enemySpawnTimer = 0.f;
        }
        else
        {
            this->enemySpawnTimer += 1.f;
        }
    }


    //Move the enemies
    for(int i = 0; i < this->enemies.size(); i++)
    {
        this->enemies[i].move(0.f, 1.f);

        //Check if clicked upon
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if(this->enemies[i].getGlobalBounds().contains(this->mousePosView))
            {
                this->enemies.erase(this->enemies.begin() + i);
            }
        }
    }
}

void Game::update()
{
    this->pollEvents();

    this->updateMousePositions();

    this->updateEnemies();
}

void Game::renderEnemies()
{
    //Rendering all the enemies
    for(auto &i : this->enemies)
    {
        this->window->draw(i);
    }
}

void Game::render()
{
    /*
        Renders the game objects
    */

    this->window->clear(sf::Color(255, 255, 255, 255)); //clear old frame

    //Draw game objects
    this->renderEnemies();

    this->window->display();
}