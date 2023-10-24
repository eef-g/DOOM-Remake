#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include <iostream>
#include <map>
#include <string>

#include<SFML/Graphics.hpp>

class Tile {
    private:
        // Variables
        sf::RectangleShape shape;
        sf::IntRect uvRect;
        sf::Texture *tileset;
        sf::Vector2u tileSize;
        sf::Vector2u tilePos;
        sf::Vector2u spritePos;

    public:
        Tile();
        Tile(sf::Texture *tileset, sf::Vector2u tileSize, sf::Vector2u tilePos, sf::Vector2u spritePos);
        virtual ~Tile();

        void update();
        void render(sf::RenderTarget *target);
};


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