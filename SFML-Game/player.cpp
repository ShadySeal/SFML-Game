#include "player.h"

Player::Player(float x, float y, sf::Texture* texture, const sf::Vector2f& boxSize)
{
	this->createSprite(texture);
	this->initAnimation();
	sprite->setOrigin(sprite->getLocalBounds().getCenter());
	this->setPosition(x, y);

	this->movementSpeed = 200.f;
	this->boxSize = boxSize;
}

Player::~Player()
{
	delete this->animation;
}

// Initializes animation frames and maps player states to animation rows
void Player::initAnimation()
{
	this->animation = new Animation(this->texture, sf::Vector2u(8, 8), 0.1f);

	sprite->setTextureRect(animation->textureRect);

	animationRowMap = {
		{PlayerState::IDLE_DOWN, 0},
		{PlayerState::IDLE_RIGHT, 1},
		{PlayerState::IDLE_LEFT, 2},
		{PlayerState::IDLE_UP, 3},
		{PlayerState::RUN_DOWN, 4},
		{PlayerState::RUN_RIGHT, 5},
		{PlayerState::RUN_LEFT, 6},
		{PlayerState::RUN_UP, 7}
	};
}

// Determines the correct animation state based on movement direction
PlayerState Player::getMovementStateFromVector(const sf::Vector2f& dir)
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

void Player::update(const float& deltaTime)
{
	originalPos = sprite->getPosition();

	sf::Vector2f direction(0.f, 0.f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		direction.x = -1.f;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		direction.x = 1.f;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
		direction.y = -1.f;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
		direction.y = 1.f;

	// Normalize the movement vector to prevent faster diagonal movement
	if (direction.x != 0.f || direction.y != 0.f)
	{
		this->move(deltaTime, direction);
	}

	// Determine animation row based on movement direction
	currentState = getMovementStateFromVector(direction);
	currentRow = animationRowMap[currentState];

	// Update sprite texture based on current animation frame
	if (animation && sprite)
	{
		animation->update(currentRow, deltaTime);
		sprite->setTextureRect(animation->textureRect);
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
