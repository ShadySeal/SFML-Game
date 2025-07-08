#pragma once

#include <iostream>
#include <vector>
#include <stack>
#include <map>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "collision_manager.h"

class Entity
{
private:

protected:
	sf::Texture* texture;
	sf::Sprite* sprite;
	float movementSpeed;

public:
	Entity();
	virtual ~Entity();

	// Functions
	virtual void move(const float& deltaTime, const sf::Vector2f direction);
	virtual void createSprite(sf::Texture* texture);
	virtual void setPosition(const float x, const float y);
	virtual sf::Vector2f getPosition() const;
	virtual sf::FloatRect getBoundingBox(const sf::Vector2f& boxSize) const;

	virtual void update(const float& deltaTime) = 0;
	virtual void render(sf::RenderTarget* target) = 0;
};
