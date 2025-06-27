#include "game.h"

// Static functions

// Initializer functions
void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode({ 800, 600 }), "SFML Game");
}

// Contructors / destructors
Game::Game()
{
    this->initWindow();
}

Game::~Game()
{
	delete this->window;
}

void Game::updateDeltaTime()
{
    // Updates the deltaTime variable with the time it takes to update and render one frame 
    this->deltaTime = this->deltaTimeClock.restart().asSeconds();
}

// Functions
void Game::updateSFMLEvents()
{
    // Check all the window's events that were triggered since the last iteration of the loop
    while (const std::optional event = this->window->pollEvent())
    {
        // "close requested" event: we close the window
        if (event->is<sf::Event::Closed>())
            this->window->close();
    }
}

void Game::update()
{
    this->updateSFMLEvents();
}

void Game::render()
{
    this->window->clear();

    // Render items
    this->window->display();
}

void Game::run()
{
    // run the program as long as the window is open
    while (this->window->isOpen())
    {
        this->updateDeltaTime();
        this->update();
        this->render();
    }
}
