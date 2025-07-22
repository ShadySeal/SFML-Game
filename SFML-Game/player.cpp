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
	delete this->animation;
}

// Initializes animation frames and maps player states to animation rows
void Player::initAnimation()
{
	this->animation = new Animation(this->texture, sf::Vector2u(4, 7));

	sprite->setTextureRect(animation->textureRect);

	animationRowMap = {
		{PlayerState::RUN_DOWN, 1},
		{PlayerState::RUN_LEFT, 2},
		{PlayerState::RUN_UP, 3},
		{PlayerState::RUN_RIGHT, 4},
		{PlayerState::ATTACK_DOWN, 5},
		{PlayerState::ATTACK_LEFT, 6}
	};

	attackSwitchTime = 0.3f;
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		dir.x -= 1.f;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		dir.x += 1.f;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
		dir.y -= 1.f;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
		dir.y += 1.f;
	return dir;
}

// Determines the correct animation state based on movement direction
PlayerState Player::getMovementState(const sf::Vector2f& dir)
{
	if (isAttacking)
	{
		// Return attack state based on last movement direction
		switch (lastDirection)
		{
		case PlayerState::RUN_UP:
			return PlayerState::ATTACK_DOWN;
		case PlayerState::RUN_DOWN:
			return PlayerState::ATTACK_DOWN;
		case PlayerState::RUN_LEFT:
			return PlayerState::ATTACK_LEFT;
		case PlayerState::RUN_RIGHT:
			return PlayerState::ATTACK_DOWN;
		default:
			return PlayerState::ATTACK_DOWN;
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

// Gets the correct idle frame from the first column of the sprite sheet based on the last direction
int Player::getIdleColumn() const
{
	switch (lastDirection)
	{
		case PlayerState::RUN_DOWN:  return 0;
		case PlayerState::RUN_LEFT:  return 1;
		case PlayerState::RUN_UP:    return 2;
		case PlayerState::RUN_RIGHT: return 3;
		default: return 0;
	}
}

void Player::update(const float& deltaTime)
{
	originalPos = sprite->getPosition();

	sf::Vector2f direction = getInputDirection();

	// Handle movement
	if (direction != sf::Vector2f(0.f, 0.f) && !isAttacking)
	{
		move(deltaTime, direction);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z) && !isAttacking)
	{
		isAttacking = true;
	}

	// Determine current state and animation row
	currentState = getMovementState(direction);
	currentRow = animationRowMap[currentState];

	// Update sprite animation
	if (animation && sprite)
	{
		if (isAttacking)
		{
			animation->update(currentRow, deltaTime, 0.1f);
			sprite->setTextureRect(animation->textureRect);

			attackTime += deltaTime;

			if (attackTime >= attackSwitchTime)
			{
				attackTime = 0.f;
				isAttacking = false;
				animation->reset();
			}
		}
		else if (direction != sf::Vector2f(0.f, 0.f))
		{
			animation->update(currentRow, deltaTime, 0.2f);
			sprite->setTextureRect(animation->textureRect);
		}
		else
		{
			animation->reset();

			int idleCol = getIdleColumn();
			setSpriteFromSheet(sf::Vector2u(32, 32), sf::Vector2u(idleCol, 0)); // row 0 = idle
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
