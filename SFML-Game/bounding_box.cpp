#include "bounding_box.h"

BoundingBox::BoundingBox(const sf::FloatRect& box)
{
	this->box = box;
}

BoundingBox::~BoundingBox()
{
}
