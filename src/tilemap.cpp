#include "tilemap.hpp"


#pragma region Tile Code
    /// @brief Default constructor
    Tile::Tile() {
        // Empty for now
    }
    /// @brief Constructor
    /// @param tileset A pointer to the texture asset that is loaded
    /// @param tileSize A Vector2u containing the size of the tile
    /// @param tilePos A Vector2u containing the location of the tile in the world
    /// @param spritePos A Vector2u containing the location of the tile sprite
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

    /// @brief Destructor
    Tile::~Tile() {

    }

    /// @brief Updates the tile
    void Tile::update() {
        // Empty for now but we'll do some checking eventually
    }

    /// @brief Renders the tile
    void Tile::render(sf::RenderTarget *target) {
        // Render the tile
        target->draw(this->shape);
    }
#pragma endregion



#pragma region Tilemap Code

    /// @brief Default constructor
    Tilemap::Tilemap() {
        this->initVariables();
        this->initTileset();
    }

    /// @brief Destructor
    Tilemap::~Tilemap() {

    }

    /// @brief Initializes the variables of the tilemap -- Currently values are hard-coded
    void Tilemap::initVariables() {
        // Store how large the map is along with the size of each tile
        this->tileSize = sf::Vector2u(16, 16);
        this->mapSize = sf::Vector2u(32, 32);

        // Load the tileset
        this->tileset.loadFromFile("assets/tilemap.png");
    }

    /// @brief Initializes the tileset
    void Tilemap::initTileset() {
        // Set up the tilemap
        for (int x = 0; x < this->mapSize.x; x++) {
            for (int y = 0; y < this->mapSize.y; y++) {
                this->addTile(x, y);
            }
        }
    }

    /// @brief  Adds a tile to the tilemap
    /// @param x The x position of the tile
    /// @param y The y position of the tile
    void Tilemap::addTile(int x, int y) {
        std::string tileName = "tile_" + std::to_string(x) + "_" + std::to_string(y);
        sf::Vector2u tilePos(x * this->tileSize.x, y * this->tileSize.y);
        sf::Vector2u spritePos(0, 0);
        this->tileMap[tileName] = Tile(&this->tileset, this->tileSize, tilePos, spritePos);
    }

    /// @brief Updates the tilemap
    void Tilemap::update() {
        for( auto &tile : this->tileMap) {
            tile.second.update();
        }
    }

    /// @brief Renders the tilemap
    /// @param target The render target to render the tilemap to
    void Tilemap::render(sf::RenderTarget *target) {
        // Render the tilemap
        for (auto &tile : this->tileMap) {
            tile.second.render(target);
        }
    }


    /// @brief Gets a tile object from coordinates
    /// @param x The x coordinate of the tile
    /// @param y The y coordinate of the tile
    /// @return Tile object at the given coordinates 
    Tile Tilemap::getTile(int x, int y) {
        std::string tileName = "tile_" + std::to_string(x) + "_" + std::to_string(y);
        return this->tileMap[tileName];
    }

#pragma endregion