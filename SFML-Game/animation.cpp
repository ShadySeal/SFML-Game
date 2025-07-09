#include "Animation.h"

Animation::Animation(sf::Texture* texture, sf::Vector2u frameCount, float switchTime)
{
	this->frameCount = frameCount;
	this->switchTime = switchTime;
	this->totalTime = 0.f;
	this->currentFrame.x = 0;

	this->textureRect.size.x = texture->getSize().x / float(frameCount.x);
	this->textureRect.size.y = texture->getSize().y / float(frameCount.y);
}

Animation::~Animation()
{
}

void Animation::update(int row, const float& deltaTime)
{
	currentFrame.y = row;
	totalTime += deltaTime;

	if (totalTime >= switchTime)
	{
		totalTime -= switchTime;
		currentFrame.x++;

		if (currentFrame.x >= frameCount.x)
		{
			currentFrame.x = 0;
		}
	}

	textureRect.position.x = currentFrame.x * textureRect.size.x;
	textureRect.position.y = currentFrame.y * textureRect.size.y;
}

void Animation::reset()
{
	currentFrame.x = 0;
	totalTime = 0.f;
	textureRect.position.x = 0;
}
