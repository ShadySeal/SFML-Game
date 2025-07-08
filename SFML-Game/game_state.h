#pragma once

#include "state.h"
#include "player.h"
#include "Level.h"

class GameState : public State
{
private:
	Player* player;
	sf::View* cameraView;

	void initTextures();

public:
	GameState(sf::RenderWindow* window);
	virtual ~GameState();

	Level* level;

	// Functions
	void endState();

	void updateKeybinds(const float& deltaTime);
	void update(const float& deltaTime);
	void render(sf::RenderTarget* target = nullptr);
};

