#include "main_menu.hpp"

namespace dv {
    void MainMenu::init() {
        // Put any texture loading here if needed
    }

    void MainMenu::draw() {
        switch(this->menu_state) {
            case 0:
                this->drawMain();
                break;
            case 1:
                this->drawSettings();
                break;
        }
    }


    void MainMenu::update() {
        switch(this->menu_state) {
            case 0:
                this->updateMain();
                break;
            case 1:
                this->updateSettings();
                break;
        }
    }

    void MainMenu::drawMain() {
        DrawText("Doom Clone", 190, 100, 40, this->TEXT_COLOR);
        DrawRectangleRec(this->playRec, this->playColor);
        DrawText(this->playText.c_str(), this->playRec.x + 10, this->playRec.y + 10, 30, this->TEXT_COLOR);
        DrawRectangleRec(this->menuRec, this->menuColor);
        DrawText(this->menuText.c_str(), this->menuRec.x + 10, this->menuRec.y + 10, 30, this->TEXT_COLOR);
        DrawRectangleRec(this->quitRec, this->quitColor);
        DrawText(this->quitText.c_str(), this->quitRec.x + 10, this->quitRec.y + 10, 30, this->TEXT_COLOR);
    }

    void MainMenu::drawSettings() {
        DrawText("Settings", 190, 100, 40, this->TEXT_COLOR);
        DrawRectangleRec(this->backRec, this->backColor);
        DrawText(this->backText.c_str(), this->backRec.x + 10, this->backRec.y + 10, 30, this->TEXT_COLOR);

        DrawRectangleRec(this->loadWADRec, this->loadWADColor);
        DrawText(this->loadWADText.c_str(), this->loadWADRec.x + 10, this->loadWADRec.y + 10, 30, this->TEXT_COLOR);

        DrawRectangleRec(this->selectWADRec, this->selectWADColor);
        DrawText(this->selectWADText.c_str(), this->selectWADRec.x + 10, this->selectWADRec.y + 10, 30, this->TEXT_COLOR);

        if(this->wad_count > 0) {
            DrawRectangleRec(this->leftArrowRec, this->leftArrowColor);
            DrawText(this->leftArrowText.c_str(), this->leftArrowRec.x + 10, this->rightArrowRec.y, 30, this->TEXT_COLOR);
        }

        if(this->wad_count < this->wad_count) {
            DrawRectangleRec(this->rightArrowRec, this->rightArrowColor);
            DrawText(this->rightArrowText.c_str(), this->rightArrowRec.x + 10, this->rightArrowRec.y + 10, 30, this->TEXT_COLOR);
        }

        DrawRectangleRec(this->loadWADRec, this->loadWADColor);
        DrawText(this->loadWADText.c_str(), this->loadWADRec.x + 10, this->loadWADRec.y + 10, 30, this->TEXT_COLOR);

        DrawRectangleRec(this->mapTestRec, this->mapTestColor);
        DrawText(this->mapTestText.c_str(), this->mapTestRec.x + 10, this->mapTestRec.y + 10, 30, this->TEXT_COLOR);
    }

    void MainMenu::updateMain() {
        if(CheckCollisionPointRec(GetMousePosition(), this->playRec)) {
            this->playColor= this->HOVER_COLOR;
            this->playText = "> Play";
        } else {
            this->playText = "Play";
            this->playColor = this->BACKGROUND_COLOR;
        }

        if(CheckCollisionPointRec(GetMousePosition(), this->menuRec)) {
            this->menuColor= this->HOVER_COLOR;
            this->menuText = "> Menu";
        } else {
            this->menuText = "Menu";
            this->menuColor = this->BACKGROUND_COLOR;
        }

        if(CheckCollisionPointRec(GetMousePosition(), this->quitRec)) {
            this->quitColor= this->HOVER_COLOR;
            this->quitText = "> Quit";
        } else {
            this->quitColor = this->BACKGROUND_COLOR;
            this->quitText = "Quit";
        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (CheckCollisionPointRec(GetMousePosition(), this->playRec)) {
                std::cout << "Play Button pressed" << std::endl;
            }
            if (CheckCollisionPointRec(GetMousePosition(), this->menuRec)) {
                this->menu_state = 1;
            }
            if (CheckCollisionPointRec(GetMousePosition(), this->quitRec)) {
                std::cout << "Quit Button pressed" << std::endl;
                CloseWindow();
            }
        }
    }

    void MainMenu::updateSettings() {
        if(CheckCollisionPointRec(GetMousePosition(), this->backRec)) {
            this->backColor= this->HOVER_COLOR;
            this->backText = "> Back";
        } else {
            this->backText = "Back";
            this->backColor = this->BACKGROUND_COLOR;
        }

        if(CheckCollisionPointRec(GetMousePosition(), this->loadWADRec)) {
            this->loadWADColor= this->HOVER_COLOR;
            this->loadWADText = "> Load WAD";
        } else {
            this->loadWADText = "Load WAD";
            this->loadWADColor = this->BACKGROUND_COLOR;
        }

        if(CheckCollisionPointRec(GetMousePosition(), this->mapTestRec)) {
            this->mapTestColor= this->HOVER_COLOR;
            this->mapTestText = "> Map Test";
        } else {
            this->mapTestText = "Map Test";
            this->mapTestColor = this->BACKGROUND_COLOR;
        }


        if(CheckCollisionPointRec(GetMousePosition(), this->leftArrowRec) && this->wad_index > 0) {
            this->leftArrowColor= this->HOVER_COLOR;
        } else {
            this->leftArrowColor = this->BACKGROUND_COLOR;
        }

        if(CheckCollisionPointRec(GetMousePosition(), this->rightArrowRec) && this->wad_index < this->wad_count) {
            this->rightArrowColor= this->HOVER_COLOR;
        } else {
            this->rightArrowColor = this->BACKGROUND_COLOR;
        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (CheckCollisionPointRec(GetMousePosition(), this->backRec)) {
                this->menu_state = 0;
            }
            if (CheckCollisionPointRec(GetMousePosition(), this->loadWADRec)) {
                std::cout << "Load WAD Button pressed" << std::endl;
            }
            if (CheckCollisionPointRec(GetMousePosition(), this->leftArrowRec) && this->wad_index > 0) {
                std::cout << "Left Arrow Button pressed" << std::endl;
            }
            if (CheckCollisionPointRec(GetMousePosition(), this->rightArrowRec) && this->wad_index < this->wad_count) {
                std::cout << "Right Arrow Button pressed" << std::endl;
            }
            if (CheckCollisionPointRec(GetMousePosition(), this->mapTestRec)) {
                std::cout << "Map Test Button pressed" << std::endl;
            }
            if (CheckCollisionPointRec(GetMousePosition(), this->mapTestRec)) {
                // Switch to map testing
                this->view->setGameState(GameState::MAP_TESTING);
            }
        }
    }



}