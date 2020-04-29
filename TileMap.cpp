#include "TileMap.h"

TileMap::TileMap(std::vector<std::vector<int>> startTiles, int startTileSize, sf::Texture startTileset)
{
	tiles = startTiles;
	tileSize = startTileSize;
	tileSet = startTileset;

	height = tiles.size();
	width = tiles[0].size();

	vertices.setPrimitiveType(sf::Quads);
	vertices.resize(width * height * 4);

	load();
}

TileMap::~TileMap(){}

void TileMap::load()
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			// get tile number
			int tileNumber = tiles[i][j];
			
			// find pos in tileset texture
			int tu = tileNumber % (tileSet.getSize().x / tileSize);
			int tv = tileNumber / (tileSet.getSize().x / tileSize);

			// get pointer to current tile's quad
			sf::Vertex* quad = &vertices[(j + i * width) * 4];

			// define corners of quad
			quad[0].position = sf::Vector2f(j * tileSize, i * tileSize);
			quad[1].position = sf::Vector2f((j + 1) * tileSize, i * tileSize);
			quad[2].position = sf::Vector2f((j + 1) * tileSize, (i + 1) * tileSize);
			quad[3].position = sf::Vector2f(j * tileSize, (i + 1) * tileSize);

			// define texture coordinates
			quad[0].texCoords = sf::Vector2f(tu * tileSize, tv * tileSize);
			quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize, tv * tileSize);
			quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize, (tv + 1) * tileSize);
			quad[3].texCoords = sf::Vector2f(tu * tileSize, (tv + 1) * tileSize);
		}
	}
}

void TileMap::SetTiles(std::vector<std::vector<int>> newTiles)
{
	tiles = newTiles;
	load();
}