#pragma once

#include "state.h"

class Game
{
private:
	// Variables
	sf::RenderWindow *window;

	sf::Clock deltaTimeClock;
	float deltaTime;

	// Initialization
	void initWindow();

public:
	// Contructors / destructors
	Game();
	virtual ~Game();

	// Functions
	void updateDeltaTime();
	void updateSFMLEvents();
	void update();
	void render();
	void run();
};

