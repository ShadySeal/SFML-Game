#include "entity.h"

Entity::Entity()
{
	this->texture = NULL;
	this->sprite = NULL;
	this->movementSpeed = 100.f;
}

Entity::~Entity()
{
	delete this->sprite;
}

void Entity::move(const float& deltaTime, const sf::Vector2f direction)
{

	this->sprite->move(direction * deltaTime * this->movementSpeed);
}

void Entity::createSprite(sf::Texture* texture)
{
	this->texture = texture;
	this->sprite = new sf::Sprite(*this->texture);
}

void Entity::setPosition(const float x, const float y)
{
	if (this->sprite)
	{
		this->sprite->setPosition({ x, y });
	}
}

sf::Vector2f Entity::getPosition() const
{
	return this->sprite->getPosition();
}

sf::FloatRect Entity::getBoundingBox(const sf::Vector2f& boxSize) const
{
	sf::Vector2f center = sprite->getGlobalBounds().getCenter();
	sf::FloatRect box({ center.x - boxSize.x / 2.f, center.y - boxSize.y / 2.f, }, { boxSize.x, boxSize.y });
	CollisionManager::getInstance().playerBox = box;
	return box;
}

void Entity::setSpriteFromSheet(sf::Vector2u gridSize, sf::Vector2u currentFrame)
{
	sf::IntRect textureRect;

	unsigned int frameWidth = texture->getSize().x / gridSize.x;
	unsigned int frameHeight = texture->getSize().y / gridSize.y;

	textureRect.position.x = currentFrame.x * frameWidth;
	textureRect.position.y = currentFrame.y * frameHeight;
	textureRect.size.x = frameWidth;
	textureRect.size.y = frameHeight;

	sprite->setTextureRect(textureRect);
}
