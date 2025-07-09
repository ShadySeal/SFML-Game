#include "player.h"

Player::Player(float x, float y, sf::Texture* texture, const sf::Vector2f& boxSize)
{
	this->createSprite(texture);
	this->initAnimation();
	sprite->setOrigin(sprite->getLocalBounds().getCenter());
	this->setPosition(x, y);

	this->movementSpeed = 100.f;
	this->boxSize = boxSize;
}

Player::~Player()
{
	delete this->walkAnim;
}

// Initializes animation frames and maps player states to animation rows
void Player::initAnimation()
{
	this->walkAnim = new Animation(this->texture, sf::Vector2u(4, 5), 0.2f);

	sprite->setTextureRect(walkAnim->textureRect);

	animationRowMap = {
		{PlayerState::IDLE_DOWN, 0},
		{PlayerState::IDLE_RIGHT, 0},
		{PlayerState::IDLE_LEFT, 0},
		{PlayerState::IDLE_UP, 0},
		{PlayerState::RUN_DOWN, 1},
		{PlayerState::RUN_RIGHT, 2},
		{PlayerState::RUN_LEFT, 3},
		{PlayerState::RUN_UP, 4}
	};
}

void Player::checkCollisions()
{
	sf::FloatRect playerBox = getBoundingBox(boxSize);

	for (const auto& tileBoxes : CollisionManager::getInstance().tileBoxes)
	{
		if (playerBox.findIntersection(tileBoxes))
		{
			sprite->setPosition(originalPos);
		}
	}
}

sf::Vector2f Player::getInputDirection() const
{
	sf::Vector2f dir(0.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))  dir.x -= 1.f;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) dir.x += 1.f;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))    dir.y -= 1.f;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))  dir.y += 1.f;
	return dir;
}

// Determines the correct animation state based on movement direction
PlayerState Player::getMovementState(const sf::Vector2f& dir)
{
	if (dir.x == 0 && dir.y == 0)
	{
		// No movement: return idle state based on last movement direction
		switch (lastDirection)
		{
		case PlayerState::RUN_UP:
			return PlayerState::IDLE_UP;
		case PlayerState::RUN_DOWN:
			return PlayerState::IDLE_DOWN;
		case PlayerState::RUN_LEFT:
			return PlayerState::IDLE_LEFT;
		case PlayerState::RUN_RIGHT:
			return PlayerState::IDLE_RIGHT;
		default:
			return PlayerState::IDLE_DOWN;
		}
	}

	// Update lastDirection based on dominant axis
	if (std::abs(dir.x) > std::abs(dir.y))
	{
		lastDirection = dir.x > 0 ? PlayerState::RUN_RIGHT : PlayerState::RUN_LEFT;
	}
	else if (std::abs(dir.x) < std::abs(dir.y))
	{
		lastDirection = dir.y > 0 ? PlayerState::RUN_DOWN : PlayerState::RUN_UP;
	}

	return lastDirection;
}

int Player::getIdleColumn() const
{
	switch (lastDirection)
	{
		case PlayerState::RUN_DOWN:  return 0;
		case PlayerState::RUN_RIGHT: return 1;
		case PlayerState::RUN_LEFT:  return 2;
		case PlayerState::RUN_UP:    return 3;
		default: return 0;
	}
}

void Player::update(const float& deltaTime)
{
	originalPos = sprite->getPosition();

	sf::Vector2f direction = getInputDirection();

	// Handle movement
	if (direction != sf::Vector2f(0.f, 0.f))
	{
		move(deltaTime, direction);
	}

	// Determine current state and animation row
	currentState = getMovementState(direction);
	currentRow = animationRowMap[currentState];

	// Update sprite animation
	if (walkAnim && sprite)
	{
		if (direction != sf::Vector2f(0.f, 0.f))
		{
			walkAnim->update(currentRow, deltaTime);
			sprite->setTextureRect(walkAnim->textureRect);
		}
		else
		{
			walkAnim->reset();

			int idleCol = getIdleColumn();
			setSpriteFromSheet(sf::Vector2u(4, 5), sf::Vector2u(idleCol, 0)); // row 0 = idle
		}
	}

	checkCollisions();
}

void Player::render(sf::RenderTarget* target)
{
	if (this->sprite)
	{
		target->draw(*this->sprite);
	}
}
