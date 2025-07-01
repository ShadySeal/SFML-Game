#include "game_state.h"

GameState::GameState(sf::RenderWindow* window) : State(window)
{
	this->initTextures();
	this->player = new Player(100, 100, &this->textures["PLAYER_IDLE"]);
}

GameState::~GameState()
{
}

void GameState::initTextures()
{
	sf::Texture temp;
	temp.loadFromFile("smiley.png");
	this->textures["PLAYER_IDLE"] = temp;
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

	this->player->update(deltaTime);
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	this->player->render(target);
}
