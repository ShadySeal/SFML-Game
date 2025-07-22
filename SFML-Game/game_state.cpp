#include "game_state.h"

GameState::GameState(sf::RenderWindow* window) : State(window)
{
	this->initTextures();
	this->player = new Player(200, 100, &this->textures["PLAYER_IDLE"], sf::Vector2f({ 12.f, 16.f }));
	this->level = new Level();

	this->cameraView = new sf::View(sf::FloatRect({ 0, 0 }, { 320, 240 }));
}

GameState::~GameState()
{
	delete this->player;
	delete this->level;
	delete this->cameraView;
}

void GameState::initTextures()
{
	sf::Texture temp;
	temp.loadFromFile("resources/images/sprites/player/alpo_sprite_sheet.png");
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

	this->level->render(target);
	this->player->render(target);

	cameraView->setCenter(player->getPosition());
	target->setView(*cameraView);

	CollisionManager::getInstance().drawBoxes(target, true);
}
