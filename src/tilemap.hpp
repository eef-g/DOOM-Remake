#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include <iostream>
#include <map>
#include <string>

#include<SFML/Graphics.hpp>
/*
    The Tile class acts as a container for all of the tile's logic.
    It will contain the tile's sprite, and will be responsible for updating
    and rendering the tile.
*/

/// @brief The Tile class acts as a container for all of the tile's logic.
class Tile {
    private:
        // Variables
        sf::RectangleShape shape;

    public:
        Tile();
        Tile(sf::Texture *tileset, sf::Vector2u tileSize, sf::Vector2u tilePos, sf::Vector2u spritePos);
        virtual ~Tile();

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

            // Map handling
        std::map<std::string, Tile> tileMap;

        void initVariables();
        void initTileset();
        void addTile(int x, int y);
    public:
        Tilemap();
        virtual ~Tilemap();

        void update();
        void render(sf::RenderTarget *target);
        Tile getTile(int x, int y);
};

#endif