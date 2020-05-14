/******************************************************************************
 * Filename: TileMap.h
 * FileType: C++ Header File
 * Authors: James Olsen (1000060387) & Mason Soroka-Gill (1000049111)
 * Created On: 06/05/2020
 * Description: Handles drawing of the tile map + casting light
 *****************************************************************************/

#ifndef TILEMAP_H
#define TILEMAP_H

#include <iostream>
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "TileType.h"

#define VIEW_DISTANCE 12
#define DEGREES_CIRCLE 360.0f
#define RAY_STEP 0.2f
#define DEGREE_TO_RADIAN_FACTOR 0.01745329f

class TileMap : public sf::Drawable, public sf::Transformable
{
private:
	std::vector<std::vector<TileType>> tiles;
	std::vector<std::vector<TileType>> litMask;
	int tileSize;
	sf::Texture tileSet;
	int width;
	int height;
	sf::VertexArray vertices;
	
	void init();
	void load();

	// From SFML docs
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		// apply the transform
		states.transform *= getTransform();

		// apply the tileset texture
		states.texture = &tileSet;

		// draw the vertex array
		target.draw(vertices, states);
	}

public:
	TileMap(std::vector<std::vector<TileType>> startTiles, int startTileSize, sf::Texture startTileset);
	~TileMap();

	void SetTiles(std::vector<std::vector<TileType>> newTiles);
    void CastLight(float playerX, float playerY, bool increasedVision);
	std::vector<std::vector<bool>> LitMaskToFogOfWar();
	
};

#endif
