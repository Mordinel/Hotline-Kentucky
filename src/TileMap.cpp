/******************************************************************************
 * Filename: TileMap.cpp
 * FileType: C++ Source File
 * Authors: James Olsen (1000060387) & Mason Soroka-Gill (1000049111)
 * Created On: 06/05/2020
 * Description: Handles drawing of the tile map + casting light
 *****************************************************************************/

#include "TileMap.h"

/*
 * Constructor for the TileMap Class
 *
 * Parameters:
 *      startTiles - The initial tile map
 *      startTileSize - the size of the tiles in pixels
 *      startTileSet - the tile set texture
 */
TileMap::TileMap(std::vector<std::vector<TileType>> startTiles, int startTileSize, sf::Texture startTileset)
{
    litMask = startTiles;
	tiles = startTiles;
	tileSize = startTileSize;
	tileSet = startTileset;

    vertices.setPrimitiveType(sf::Quads);

	init();
}

/*
 * Destructor for the TileMap class
 */
TileMap::~TileMap(){}

/*
 * Method to initialize the tile map both from constructor and re-initializing later
 */
void TileMap::init()
{
    height = tiles.size();
	width = tiles[0].size();

	vertices.resize(width * height * 4);

    // make lit mask fully unlit
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            litMask[i][j] = TileType::Unlit;
        }
    }

    load();
}

/*
 * Sets the texture positions of each vertex in each quad so the GPU can render the tile map.
 */
void TileMap::load()
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			// get tile number
			int tileNumber = (int)(litMask[i][j]);
			
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
			quad[0].texCoords = sf::Vector2f((tu * tileSize) + 1, tv * tileSize);
			quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize, tv * tileSize);
			quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize, (tv + 1) * tileSize);
			quad[3].texCoords = sf::Vector2f((tu * tileSize) + 1, (tv + 1) * tileSize);

		}
	}
}

/*
 * Sets up a new tile map based on a new set of tiles
 */
void TileMap::SetTiles(std::vector<std::vector<TileType>> newTiles)
{
	tiles = newTiles;
    litMask = newTiles;

    init();
}
/*
 * Uses ray casting to figure out which tiles should be visible to the player.
 * 
 * Parameters:
 *      playerX - the players x position
 *      playerY - the players y position
 *      increasedDistance - Whether the ray casts distance should be increased
 */
void TileMap::CastLight(float playerX, float playerY, bool increasedDistance) {
    int i;
    int j;
    float x;
    float ox;
    float y;
    float oy;
    float d;
    int distance;
    
    distance = VIEW_DISTANCE;
    if (increasedDistance) {
        distance *= 2;
    }

    TileType newTile;

    playerX /= tileSize;
    playerY /= tileSize;

    // makes tiles dark if they have been seen
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {

            switch (litMask[i][j]) {
                case TileType::Floor:
                    newTile = TileType::FloorDark;
                    break;
                case TileType::Wall:
                    newTile = TileType::WallDark;
                    break;
                default:
                    newTile = litMask[i][j];
                    break;
            }

            litMask[i][j] = newTile;
        }
    }
 
    // cast rays from the player
    for (d = 0.0f; d < 360.0f; d+=0.2f) {
        // getting gradient in radians
        x = std::cos(d * 0.01745329f);
        y = std::sin(d * 0.01745329f);

        ox = playerX;
        oy = playerY;

        // walk the ray from the player, setting each tile to be lit until a wall or the limit is reached.
        for (j = 0; j < distance; j++) {

            // if the tile exceeds the bounds,  break
            if ((int)oy >= height || (int)ox >= width) {
                break;
            }

            if ((int)oy < 0 || (int)ox < 0) {
                break;
            }

            // set the tiletype to the tiletype from the regular map
            litMask[(int)oy][(int)ox] = tiles[(int)oy][(int)ox];

            // if the tile just set is a wall, break
            if (litMask[(int)oy][(int)ox] == TileType::Wall) {
                break;
            }

            // if tile is void, break
            if(litMask[(int)oy][(int)ox] == TileType::Void) {
                break;
            }

            // go to next tile along ray
            ox += x;
            oy += y;
        }
    }

    load();
}

/*
 * Creates a boolean fog of war map based on what's visible to the player.
 * 
 * Returns:
 *      A matrix of boolean values that represent whether a tile is visible or not to the player.
 */
std::vector<std::vector<bool>> TileMap::LitMaskToFogOfWar() {
    std::vector<std::vector<bool>> fogOfWar;

    for (int i = 0; i < height; i++) {
        std::vector<bool> row;

        for (int j = 0; j < width; j++) {

            switch (litMask[i][j]) {
                case TileType::FloorDark:
                case TileType::WallDark:
                case TileType::Void:
                case TileType::Unlit:
                    row.push_back(false);
                    break;
                default:
                    row.push_back(true);
                    break;
            }   
        }

        fogOfWar.push_back(row);
    }

    return fogOfWar;
}
