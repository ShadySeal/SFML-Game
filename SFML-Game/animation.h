#pragma once

#include "entity.h"

class Animation
{
private:
	sf::Vector2u frameCount;
	sf::Vector2u currentFrame;

	float totalTime;

public:
	Animation(sf::Texture* texture, sf::Vector2u frameCount);
	virtual ~Animation();

	sf::IntRect textureRect;
	
	void update(int row, const float& deltaTime, float switchTime);
	void reset();
};
