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

    /// @brief Gets the vertex of the tile
    /// @return The vertex of the tile
    sf::Vertex* Tile::getVerticies() {
        sf::FloatRect bounds = this->shape.getGlobalBounds();

        sf::Vertex quad[4];
        quad[0].position = sf::Vector2f(bounds.left, bounds.top);
        quad[1].position = sf::Vector2f(bounds.left + bounds.width, bounds.top);
        quad[2].position = sf::Vector2f(bounds.left + bounds.width, bounds.top + bounds.height);
        quad[3].position = sf::Vector2f(bounds.left, bounds.top + bounds.height);
        return quad;
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

        // Allocate memory for the layers
        this->groundLayer = new Tile*[this->mapSize.x];
        this->objectLayer = new Tile*[this->mapSize.x];
        for (int i = 0; i < this->mapSize.x; i++) {
            this->groundLayer[i] = new Tile[this->mapSize.y];
            this->objectLayer[i] = new Tile[this->mapSize.y];
        }
    }

    /// @brief Initializes the tileset
    void Tilemap::initTileset() {
        // Set up the ground layer
        for (int x = 0; x < this->mapSize.x - 1; x++) {
            for (int y = 0; y < this->mapSize.y - 1; y++) {
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
        sf::Vector2u tilePos(x * this->tileSize.x, y * this->tileSize.y);
        sf::Vector2u spritePos;
        switch(z) {
            case 0:
                spritePos = sf::Vector2u(0, 0);
                this->groundLayer[x][y] = Tile(&this->tileset, this->tileSize, tilePos, spritePos);
                this->groundLayer[x][y].isActive = true;
                break;
            case 1:
                spritePos = sf::Vector2u(2 * this->tileSize.x, 0);
                this->objectLayer[x][y] = Tile(&this->tileset, this->tileSize, tilePos, spritePos);
                this->objectLayer[x][y].isActive = true;
                break;
            default:
                break;
        }
    }

    /// @brief Updates the tilemap
    void Tilemap::update() {
        // Update the ground layer
        for(int x = 0; x < this->mapSize.x - 1; x++) {
            for(int y = 0; y < this->mapSize.y - 1; y++) {
                this->groundLayer[x][y].update();
            }
        }

        // Update the object layer
        for(int x = 0; x < this->mapSize.x - 1; x++) {
            for(int y = 0; y < this->mapSize.y - 1; y++) {
                this->objectLayer[x][y].update();
            }
        }
    }

    /// @brief Renders the tilemap
    /// @param target The render target to render the tilemap to
    void Tilemap::render(sf::RenderTarget *target) {
        // // // Create a map for batch rendering
        // std::map<const sf::Texture*, std::vector<sf::Vertex>> map;

        // // Add the ground layer to the map
        // for(int x = 0; x < this->mapSize.x -1; x++) {
        //     for(int y = 0; y < this->mapSize.y -1; y++) {
        //         const sf::Texture* texture = this->groundLayer[x][y].shape.getTexture();
        //         sf::Vertex* verts = this->groundLayer[x][y].getVerticies();
        //         for(int i = 0; i < 4; i++) {
        //             map[texture].push_back(verts[i]);
        //         }
        //     }
        // }

        // // Render the tiles using batch rendering
        // for (auto& pair : map) {
        //     const sf::Texture* texture = pair.first;
        //     const std::vector<sf::Vertex>& vertices = pair.second;
        //     target->draw(&vertices[0], vertices.size(), sf::Quads, sf::RenderStates(texture));
        // }

        // Render the ground layer
        for(int x = 0; x < this->mapSize.x - 1; x++) {
            for(int y = 0; y < this->mapSize.y - 1; y++) {
                this->groundLayer[x][y].render(target);
            }
        }

        // Render the object layer
        for(int x = 0; x < this->mapSize.x - 1; x++) {
            for(int y = 0; y < this->mapSize.y - 1; y++) {
                this->objectLayer[x][y].render(target);
            }
        }
    }

    /// @brief Gets a tile object from coordinates
    /// @param x The x coordinate of the tile
    /// @param y The y coordinate of the tile
    /// @return Tile object at the given coordinates 
    Tile Tilemap::getTile(int x, int y, int z) {
        switch (z) {
            case 0:
                return this->groundLayer[x][y];
                break;
            case 1:
                return this->objectLayer[x][y];
                break;
            default:
                return this->groundLayer[x][y];
                break;
        }
    }

#pragma endregion