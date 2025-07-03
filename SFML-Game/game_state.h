#pragma once

#include "state.h"
#include "player.h"
#include "tile_map.h"

class GameState : public State
{
private:
	Player* player;
	TileMap* tileMap;
	sf::View* cameraView;

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

