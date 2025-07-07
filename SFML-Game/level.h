#pragma once

#include "tile_map.h"

class Level
{
private:
	void initTileMap();

public:
	Level();
	virtual ~Level();

	TileMap* tileMap;

	void render(sf::RenderTarget* target);
};
