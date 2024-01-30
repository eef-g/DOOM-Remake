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
        DrawRectangleRec(this->backRec, this->backColor);
        DrawText(this->backText.c_str(), this->backRec.x + 10, this->backRec.y + 10, 30, this->TEXT_COLOR);
        
        DrawRectangleRec(this->mapTitleRec, this->mapTitleColor);
        DrawText(this->mapTitleText.c_str(), this->mapTitleRec.x + 10, this->mapTitleRec.y + 10, 30, this->TEXT_COLOR);

        DrawRectangleRec(this->loadRec, this->loadColor);
        DrawText(this->loadText.c_str(), this->loadRec.x + 50, this->loadRec.y + 10, 30, this->TEXT_COLOR);

        DrawRectangleRec(this->leftArrowRec, this->leftArrowColor);
        DrawText(this->leftArrowText.c_str(), this->leftArrowRec.x + 10, this->leftArrowRec.y + 10, 30, this->TEXT_COLOR);
        DrawRectangleRec(this->rightArrowRec, this->rightArrowColor);
        DrawText(this->rightArrowText.c_str(), this->rightArrowRec.x + 10, this->rightArrowRec.y + 10, 30, this->TEXT_COLOR);

        if(this->mapLoaded) {
            // Draw the map similarly to how the top-down 2D map was previously
        }
    }
}