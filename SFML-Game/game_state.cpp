#include "game_state.h"

GameState::GameState(sf::RenderWindow* window) : State(window)
{
}

GameState::~GameState()
{
}

void GameState::endState()
{
	std::cout << "Ending GameState!" << "\n";
}

void GameState::updateKeybinds(const float& deltaTime)
{
	this->checkForQuit();
}

void GameState::update(const float& deltaTime)
{
	this->updateKeybinds(deltaTime);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		std::cout << "A" << "\n";
}

void GameState::render(sf::RenderTarget* target)
{

}
