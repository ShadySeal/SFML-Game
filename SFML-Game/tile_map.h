#pragma once

#include "entity.h"

class TileMap : public sf::Drawable, public sf::Transformable
{
private:
	sf::VertexArray m_vertices;
	sf::Texture     m_tileset;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	TileMap();
	virtual ~TileMap();

	bool load(const std::filesystem::path& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height, const std::unordered_set<int>& collisionTiles);
};
