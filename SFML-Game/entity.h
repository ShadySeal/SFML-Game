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
	sf::RectangleShape shape;
	float movementSpeed;

public:
	Entity();
	virtual ~Entity();
	virtual void move(const float& deltaTime, const float x, const float y);

	// Functions
	virtual void update(const float& deltaTime);
	virtual void render(sf::RenderTarget* target);
};

