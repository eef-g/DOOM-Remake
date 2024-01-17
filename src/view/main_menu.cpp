#include "main_menu.hpp"

namespace dv {
    MainMenu::MainMenu() {
        this->dropDownBoxState = 0;
    }

    MainMenu::~MainMenu() {

    }

    void MainMenu::draw() {
        if(GuiDropdownBox((Rectangle){ 100, 100, 200, 20 }, "TicTacToe;Chess;Checkers", &dropDownBoxState, true)) {
            switch(this->dropDownBoxState) {
                case 0:
                    std::cout << "TicTacToe" << std::endl;
                    break;
                case 1:
                    std::cout << "Chess" << std::endl;
                    break;
                case 2:
                    std::cout << "Checkers" << std::endl;
                    break;
            }
        }
    }

    void MainMenu::update() {

    }
}