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
        // Set up the ground layer
        for (int x = 0; x < this->mapSize.x; x++) {
            for (int y = 0; y < this->mapSize.y; y++) {
                this->addTile(x, y, 0, TileType::GROUND);
            }
        }

        // Set up the object layer
        // Create the list of tiles that will have an object - -This is only temp
        std::vector<sf::Vector2u> objectTiles;
        objectTiles.push_back(sf::Vector2u(10, 12));
        objectTiles.push_back(sf::Vector2u(11, 12));
        objectTiles.push_back(sf::Vector2u(10, 13));
        objectTiles.push_back(sf::Vector2u(11, 13));
        for (auto &tile : objectTiles) {
            this->addTile(tile.x, tile.y, 1, TileType::OBJECT);
        }
    }

    /// @brief  Adds a tile to the tilemap
    /// @param x The x position of the tile
    /// @param y The y position of the tile
    void Tilemap::addTile(int x, int y, int z, TileType type) {
        std::string tileName = "tile_" + std::to_string(x) + "_" + std::to_string(y);
        sf::Vector2u tilePos(x * this->tileSize.x, y * this->tileSize.y);
        sf::Vector2u spritePos;
        switch(z) {
            case 0:
                spritePos = sf::Vector2u(0, 0);
                this->groundLayer[tileName] = Tile(&this->tileset, this->tileSize, tilePos, spritePos);
                break;
            case 1:
                spritePos = sf::Vector2u(32, 0);
                this->objectLayer[tileName] = Tile(&this->tileset, this->tileSize, tilePos, spritePos);
                break;
            default:
                break;
        }
    }

    /// @brief Updates the tilemap
    void Tilemap::update() {
        // Update the ground layer
        for( auto &tile : this->groundLayer) {
            tile.second.update();
        }

        // Update the object layer
        for( auto &tile : this->objectLayer) {
            tile.second.update();
        }
    }

    /// @brief Renders the tilemap
    /// @param target The render target to render the tilemap to
    void Tilemap::render(sf::RenderTarget *target) {
        // Render the ground layer
        for (auto &tile : this->groundLayer) {
            tile.second.render(target);
        }

        // Render the object layer
        for (auto &tile : this->objectLayer) {
            tile.second.render(target);
        }
    }

    /// @brief Gets a tile object from coordinates
    /// @param x The x coordinate of the tile
    /// @param y The y coordinate of the tile
    /// @return Tile object at the given coordinates 
    Tile Tilemap::getTile(int x, int y, int z) {
        std::string tileName = "tile_" + std::to_string(x) + "_" + std::to_string(y);
        switch (z) {
            case 0:
                return this->groundLayer[tileName];
                break;
            case 1:
                return this->objectLayer[tileName];
                break;
            default:
                return this->groundLayer[tileName];
                break;
        }
    }

#pragma endregion