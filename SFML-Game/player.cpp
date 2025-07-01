#include "player.h"

Player::Player(float x, float y, sf::Texture* texture)
{
	this->createSprite(texture);
	this->setPosition(x, y);
}

Player::~Player()
{
}

void Player::update(const float& deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		this->move(deltaTime, -1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		this->move(deltaTime, 1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
		this->move(deltaTime, 0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
		this->move(deltaTime, 0.f, 1.f);
}
