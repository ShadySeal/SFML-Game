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
	std::map<std::string, Animation> animations;
	int currentRow;
	std::unordered_map<PlayerState, unsigned int> animationRowMap;
	PlayerState currentState;
	PlayerState lastDirection;

	sf::Vector2f boxSize;

	sf::Vector2f originalPos;
	sf::Keyboard::Key lastDirectionKey;

	bool isAttacking = false;
	float attackTime;
	float attackSwitchTime;

	// Functions
	void initAnimation();
	PlayerState getMovementState(const sf::Vector2f& dir);
	void checkCollisions();
	sf::Vector2f getInputDirection() const;
	int getIdleColumn() const;

public:
	Player(float x, float y, sf::Texture* texture, const sf::Vector2f& boxSize);
	virtual ~Player();

	// Functions
	void update(const float& deltaTime);
	void render(sf::RenderTarget* target);
};
