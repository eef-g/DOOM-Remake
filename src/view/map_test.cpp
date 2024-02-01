#include "map_test.hpp"

namespace dv {
    //TODO: Implement the Map_test class
    // This means:
    /*
        1) Allowing for the user to select the map they want to view and test
        2) With a selected map, allow the user to view the map and move the player
        3) Allow the user to go to the settings menu
        -- NOTE -- Think of this as the 2D version of the actual game. This is the representation of the logic that will always be running in the background.
    */
    void MapTest::init() {
        // Put any texture loading here if needed
    }


    void MapTest::draw() {
        this->drawSettings();
        if(this->mapLoaded) {
            this->drawMap();
        }
    }

    void MapTest::drawSettings() {
        // Draw the back button
        DrawRectangleRec(this->backRec, this->backColor);
        DrawText(this->backText.c_str(), this->backRec.x + 10, this->backRec.y + 10, 30, this->TEXT_COLOR);
        // Draw the map title
        DrawRectangleRec(this->mapTitleRec, this->mapTitleColor);
        DrawText(this->mapTitleText.c_str(), this->mapTitleRec.x + 10, this->mapTitleRec.y + 10, 30, this->TEXT_COLOR);
        // Draw the load button
        DrawRectangleRec(this->loadRec, this->loadColor);
        DrawText(this->loadText.c_str(), this->loadRec.x + 50, this->loadRec.y + 10, 30, this->TEXT_COLOR);
        // Draw the left and right arrows
        DrawRectangleRec(this->leftArrowRec, this->leftArrowColor);
        DrawText(this->leftArrowText.c_str(), this->leftArrowRec.x + 10, this->leftArrowRec.y + 10, 30, this->TEXT_COLOR);
        DrawRectangleRec(this->rightArrowRec, this->rightArrowColor);
        DrawText(this->rightArrowText.c_str(), this->rightArrowRec.x + 10, this->rightArrowRec.y + 10, 30, this->TEXT_COLOR);
    }

    void MapTest::drawMap() {
        // Draw the map
        for(int i = 0; i < this->view->getController()->map_linedefs_2D.size(); i++) {
            wad::LINEDEF line = this->view->getController()->map_linedefs_2D[i];
            wad::VERTEX start = this->view->getController()->map_vertexes_2D[line.start_vertex];
            wad::VERTEX end = this->view->getController()->map_vertexes_2D[line.end_vertex];
            DrawLine(start.x, start.y, end.x, end.y, WHITE);
        }
    }


    void MapTest::update() {
        // Update the map and settings
        this->updateMap();
        this->updateSettings();
    }

    void MapTest::updateMap() {
        // Update the map
    }

    void MapTest::updateSettings() {
        // Update the settings
        // Hover Checks
        if(CheckCollisionPointRec(GetMousePosition(), this->backRec)) {
            this->backColor = this->HOVER_COLOR;
        } else {
            this->backColor = this->BACKGROUND_COLOR;
        }
        if(CheckCollisionPointRec(GetMousePosition(), this->loadRec)) {
            this->loadColor = this->HOVER_COLOR;
        } else {
            this->loadColor = this->BACKGROUND_COLOR;
        }
        if(CheckCollisionPointRec(GetMousePosition(), this->leftArrowRec)) {
            this->leftArrowColor = this->HOVER_COLOR;
        } else {
            this->leftArrowColor = this->BACKGROUND_COLOR;
        }
        if(CheckCollisionPointRec(GetMousePosition(), this->rightArrowRec)) {
            this->rightArrowColor = this->HOVER_COLOR;
        } else {
            this->rightArrowColor = this->BACKGROUND_COLOR;
        }

        // Click Checks
        if(CheckCollisionPointRec(GetMousePosition(), this->backRec) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            this->view->setGameState(GameState::MAIN_MENU);
        }
        if(CheckCollisionPointRec(GetMousePosition(), this->loadRec) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (!this->mapLoaded) {
                // TODO: Change this to load the selected map. At the moment, just load E1M1 from the doom1.wad file that is stored in the model
                this->view->getController()->SelectMap(this->mapTitleText);
                std::cout << "=-=-=- Map Loaded -=-=-" << std::endl;
                // Load the map
                this->mapLoaded = true;
            }
        }
        if(CheckCollisionPointRec(GetMousePosition(), this->leftArrowRec) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            // Load the previous map
        }
        if(CheckCollisionPointRec(GetMousePosition(), this->rightArrowRec) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            // Load the next map
        }
    }

}