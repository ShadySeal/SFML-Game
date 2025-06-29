#pragma once

#include "game_state.h"

class Game
{
private:
	// Variables
	sf::RenderWindow *window;

	sf::Clock deltaTimeClock;
	float deltaTime;

	std::stack<State*> states;

	// Initialization
	void initWindow();
	void initStates();

public:
	// Contructors / destructors
	Game();
	virtual ~Game();

	// Functions

	// Regular
	void endApplication();

	// Update
	void updateDeltaTime();
	void updateSFMLEvents();
	void update();

	// Render
	void render();

	// Core
	void run();
};
