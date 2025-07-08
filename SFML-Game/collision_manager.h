#pragma once

#include "entity.h"

class CollisionManager
{
public:
	static CollisionManager& getInstance() {
		static CollisionManager instance;
		return instance;
	}

	sf::FloatRect playerBox;
	std::vector<sf::FloatRect> tileBoxes;

	void drawBoxes(sf::RenderTarget* target, bool isActive = true);

private:
	CollisionManager() {}
};

