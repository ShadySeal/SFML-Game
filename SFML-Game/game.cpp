#include "game.h"

// Static functions

// Initializer functions
void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode({ 1920, 1080 }), "SFML Game");
}

void Game::initStates()
{
    this->states.push(new GameState(this->window));
}

// Contructors / destructors
Game::Game()
{
    this->initWindow();
    this->initStates();}

Game::~Game()
{
	delete this->window;

    while (!this->states.empty())
    {
        delete this->states.top();
        this->states.pop();
    }
}

// Functions
void Game::endApplication()
{
    std::cout << "Ending application!" << "\n";
}

void Game::updateDeltaTime()
{
    // Updates the deltaTime variable with the time it takes to update and render one frame 
    this->deltaTime = this->deltaTimeClock.restart().asSeconds();
}

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

    if (!this->states.empty())
    {
        this->states.top()->update(this->deltaTime);

        if (this->states.top()->getQuit())
        {
            this->states.top()->endState();
            delete this->states.top();
            this->states.pop();
        }
    }
    // Application end
    else
    {
        this->endApplication();
        this->window->close();
    }
}

void Game::render()
{
    this->window->clear(sf::Color::Blue);
    //this->window->setMouseCursorVisible(false);

    // Render items
    if (!this->states.empty())
        this->states.top()->render(this->window);

    this->window->display();
}

void Game::run()
{
    // Run the program as long as the window is open
    while (this->window->isOpen())
    {
        this->updateDeltaTime();
        this->update();
        this->render();
    }
}
