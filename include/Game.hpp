#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <vector>
#include <ctime>
/*
    Classs that acts as the game engine
    Wrapper class
*/
class Game
{
private:
    //Variables
    //Window
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    sf::Event ev;

    //Mouse positions
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

    //Game logic
    int points;
    float enemySpawnTimer;
    float enemySpawnTimerMax;
    unsigned int maxEnemies;

    //Game objects
    sf::RectangleShape enemy;
    std::vector<sf::RectangleShape> enemies;

    //Private functions
    void initVariables();
    void initWindow();
    void initEnemies();

public:
    //Constructors /Destructors
    Game();
    virtual ~Game();

    //Accessors
    const bool running() const;

    //Functions

    /**
     * @return void
     *
     * @brief
     * Spawns enemies and sets their colors and positions.
     *  Sets a random position.
     *  Sets a random color.
     *  Adds enemy to vector.
    */
    void spawnEnemy();

    void pollEvents();
    void updateMousePositions();

    /**
     * @return void
     *
     * @brief
     * Updates the enemy spawn timer and spawns enemies
     * when the total amount of enemies is smaller than the maximum.
     * Moves the enemies downwards.
     * Removes the enemies at the edge of the screen.
    */
    void updateEnemies();
    void update();

    void renderEnemies();
    void render();
};