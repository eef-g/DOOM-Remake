#include "tilemap.hpp"


#pragma region Tile Code
    Tile::Tile() {
        // Empty for now
    }

    Tile::Tile(
        sf::Texture *tileset,
        sf::Vector2u tileSize,
        sf::Vector2u tilePos,
        sf::Vector2u spritePos
    ) {
        this->shape = sf::RectangleShape(sf::Vector2f(tileSize.x, tileSize.y));
        this->shape.setTexture(tileset);
        this->shape.setTextureRect(sf::IntRect(spritePos.x, spritePos.y, tileSize.x, tileSize.y));
        this->shape.setPosition(sf::Vector2f(tilePos.x, tilePos.y));
    }

    Tile::~Tile() {

    }

    void Tile::update() {
        // Empty for now but we'll do some checking eventually
    }

    void Tile::render(sf::RenderTarget *target) {
        // Render the tile
        target->draw(this->shape);
    }
#pragma endregion



#pragma region Tilemap Code

    Tilemap::Tilemap() {
        this->initVariables();
        this->initTileset();
    }


    Tilemap::~Tilemap() {

    }

    void Tilemap::initVariables() {
        // Store how large the map is along with the size of each tile
        this->tileSize = sf::Vector2u(16, 16);
        this->mapSize = sf::Vector2u(32, 32);

        // Load the tileset
        this->tileset.loadFromFile("assets/tilemap.png");
    }

    void Tilemap::initTileset() {
        // Set up the tilemap
        for (int x = 0; x < this->mapSize.x; x++) {
            for (int y = 0; y < this->mapSize.y; y++) {
                this->addTile(x, y);
            }
        }
    }

    void Tilemap::addTile(int x, int y) {
        std::string tileName = "tile_" + std::to_string(x) + "_" + std::to_string(y);
        sf::Vector2u tilePos(x * this->tileSize.x, y * this->tileSize.y);
        sf::Vector2u spritePos(0, 0);
        this->tileMap[tileName] = Tile(&this->tileset, this->tileSize, tilePos, spritePos);
    }

    void Tilemap::update() {
        // Empty for now but we'll do some checking eventually
    }

    void Tilemap::render(sf::RenderTarget *target) {
        // Render the tilemap
        for (auto &tile : this->tileMap) {
            tile.second.render(target);
        }
    }

    Tile Tilemap::getTile(int x, int y) {
        std::string tileName = "tile_" + std::to_string(x) + "_" + std::to_string(y);
        return this->tileMap[tileName];
    }

#pragma endregion