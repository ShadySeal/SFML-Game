#include "game_state.h"

GameState::GameState(sf::RenderWindow* window) : State(window)
{
	this->initTextures();
	this->player = new Player(0, 0, &this->textures["PLAYER_IDLE"]);
	this->tileMap = new TileMap();

	this->cameraView = new sf::View(sf::FloatRect({ 0, 0 }, { 640, 360 }));
}

GameState::~GameState()
{
	delete this->player;
}

void GameState::initTextures()
{
	sf::Texture temp;
	temp.loadFromFile("resources/images/sprites/player/adventurer_sprite_sheet.png");
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

	this->tileMap->render(target);
	this->player->render(target);

	cameraView->setCenter(player->getPosition());
	target->setView(*cameraView);

	sf::FloatRect box = player->getBoundingBox();
	sf::RectangleShape debugBox;
	debugBox.setPosition({ box.position.x, box.position.y });
	debugBox.setSize({ box.size.x, box.size.y });
	debugBox.setFillColor(sf::Color::Transparent);
	debugBox.setOutlineColor(sf::Color::Red);
	debugBox.setOutlineThickness(1.f);

	target->draw(debugBox);

	sf::FloatRect otherBox = sf::FloatRect({40.f, 40.f}, {20.f, 20.f});
	sf::RectangleShape otherDebugBox;
	otherDebugBox.setPosition({ otherBox.position.x, otherBox.position.y });
	otherDebugBox.setSize({ otherBox.size.x, otherBox.size.y });
	otherDebugBox.setFillColor(sf::Color::Transparent);
	otherDebugBox.setOutlineColor(sf::Color::Red);
	otherDebugBox.setOutlineThickness(1.f);

	target->draw(otherDebugBox);

	if (const std::optional intersection = box.findIntersection(otherBox))
	{
		std::cout << "Intersection at: (" << intersection->position.x << ", " << intersection->position.y << ")" << "\n";
	}
}
