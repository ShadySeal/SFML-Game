#pragma once

#include "entity.h"

class BoundingBox
{
private:
	

public:
	BoundingBox(const sf::FloatRect& box);
	virtual ~BoundingBox();

	sf::FloatRect box;
};

