#pragma once

#include "entity.h"

class Animation
{
private:
	sf::Vector2u frameCount;
	sf::Vector2u currentFrame;

	float totalTime;
	float switchTime;

public:
	Animation(sf::Texture* texture, sf::Vector2u frameCount, float switchTime);
	virtual ~Animation();

	sf::IntRect textureRect;
	
	void update(int row, const float& deltaTime);
	void reset();
};

