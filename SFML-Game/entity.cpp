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

void Entity::update(const float& deltaTime)
{
}

void Entity::render(sf::RenderTarget* target)
{
	if (this->sprite)
	{
		target->draw(*this->sprite);
	}
	
}
