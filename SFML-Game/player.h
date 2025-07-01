#pragma once

#include "entity.h"

class Player : public Entity
{
private:
	/*sf::Texture playerTexture;
	sf::Sprite playerSprite;*/

public:
	Player(float x, float y, sf::Texture* texture);
	virtual ~Player();

	// Functions
	void update(const float& deltaTime);
};

