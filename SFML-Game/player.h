#pragma once

#include "entity.h"
#include "animation.h"
#include "player_state.h"
#include <unordered_map>
#include <cmath>

class Player : public Entity
{
private:
	// Variables
	Animation* animation;
	int currentRow;
	std::unordered_map<PlayerState, unsigned int> animationRowMap;
	PlayerState currentState;
	PlayerState lastDirection;

	// Functions
	void initAnimation();
	PlayerState getMovementStateFromVector(const sf::Vector2f& dir);

public:
	Player(float x, float y, sf::Texture* texture);
	virtual ~Player();

	// Functions
	sf::Vector2f getPosition() const;
	void update(const float& deltaTime);
};
