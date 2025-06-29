#include "entity.h"

Entity::Entity()
{
	this->shape.setSize(sf::Vector2f(50.f, 50.f));
	this->movementSpeed = 100.f;
}

Entity::~Entity()
{
}

void Entity::move(const float& deltaTime, const float dirX, const float dirY)
{
	this->shape.move({ dirX * this->movementSpeed * deltaTime, dirY * this->movementSpeed * deltaTime });
}

void Entity::update(const float& deltaTime)
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

void Entity::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
