#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include <iostream>
#include <map>
#include<SFML/Graphics.hpp>
/*
    The Tile class acts as a container for all of the tile's logic.
    It will contain the tile's sprite, and will be responsible for updating
    and rendering the tile.
*/

enum TileType {
    GROUND,
    OBJECT
};


/// @brief The Tile class acts as a container for all of the tile's logic.
class Tile {
    private:
        // Variables
        TileType type;
    public:
        Tile();
        Tile(sf::Texture *tileset, sf::Vector2u tileSize, sf::Vector2u tilePos, sf::Vector2u spritePos);
        virtual ~Tile();
        bool isActive = false;
        sf::RectangleShape shape;

        sf::Vertex* getVerticies();
        void update();
        void render(sf::RenderTarget *target);
};


/*
    The Tilemap class acts as a container for all of the tilemap's logic.
    It will contain the tilemap's tiles, and will be responsible for updating
    and rendering the tilemap.
*/

/// @brief The Tilemap class acts as a container for all of the tilemap's logic.
class Tilemap {
    private:
        //Variables
            // Texture handling
        sf::Texture tileset;
        sf::Vector2u tileSize;
        sf::Vector2u mapSize;

            // Map handling -- Use 2D array instead of map
        Tile** groundLayer;
        Tile** objectLayer;

        void initVariables();
        void initTileset();
        void addTile(int x, int y, int z, TileType type);
    public:
        Tilemap();
        virtual ~Tilemap();

        void update();
        void render(sf::RenderTarget *target);
        Tile getTile(int x, int y, int z);
};

#endif