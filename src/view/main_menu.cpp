#include "main_menu.hpp"

namespace dv {
    void MainMenu::init() {
        this->buttonBackground = LoadImage("resources/default_resources/button_bg.png");
        this->buttonTexture = LoadTextureFromImage(this->buttonBackground);
        this->buttonRec = { 0.0f, 0.0f, (float)this->buttonTexture.width, (float)this->buttonTexture.height };
        this->buttonColor = WHITE;
    }

    void MainMenu::draw() {
        DrawTextureRec(this->buttonTexture, this->buttonRec, { 190, 200 }, this->buttonColor);
        DrawText(this->buttonText.c_str(), 190 + (this->buttonRec.width / 8), 200 + (this->buttonRec.height/ 2), 20, BLACK);
    }

    void MainMenu::update() {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (CheckCollisionPointRec(GetMousePosition(), this->buttonRec)) {
                this->buttonColor = GRAY;
                this->buttonAction = true;
            }
        }

        if (this->buttonAction) {
            this->view->setGameState(GameState::GAME);
        }
    }
}