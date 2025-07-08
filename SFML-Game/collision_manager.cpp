#include "collision_manager.h"

void CollisionManager::drawBoxes(sf::RenderTarget* target, bool isActive)
{
	if (isActive)
	{
		sf::RectangleShape debugBox;
		debugBox.setPosition({ playerBox.position.x, playerBox.position.y });
		debugBox.setSize({ playerBox.size.x, playerBox.size.y });
		debugBox.setFillColor(sf::Color::Transparent);
		debugBox.setOutlineColor(sf::Color::Red);
		debugBox.setOutlineThickness(1.f);

		target->draw(debugBox);

		for (const auto& tileBoxes : CollisionManager::getInstance().tileBoxes)
		{
			sf::RectangleShape debugBox;
			debugBox.setPosition({ tileBoxes.position.x, tileBoxes.position.y });
			debugBox.setSize({ tileBoxes.size.x, tileBoxes.size.y });
			debugBox.setFillColor(sf::Color::Transparent);
			debugBox.setOutlineColor(sf::Color::Red);
			debugBox.setOutlineThickness(1.f);

			target->draw(debugBox);
		}
	}
}
