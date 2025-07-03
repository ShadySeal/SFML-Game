#pragma once

#include <iostream>
#include <vector>
#include <stack>
#include <map>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

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
	virtual void update(const float& deltaTime);
	virtual void render(sf::RenderTarget* target);
};
