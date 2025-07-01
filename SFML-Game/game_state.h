#pragma once

#include "state.h"
#include "player.h"

class GameState : public State
{
private:
	Player* player;

	void initTextures();

public:
	GameState(sf::RenderWindow* window);
	virtual ~GameState();

	// Functions
	void endState();

	void updateKeybinds(const float& deltaTime);
	void update(const float& deltaTime);
	void render(sf::RenderTarget* target = nullptr);
};

