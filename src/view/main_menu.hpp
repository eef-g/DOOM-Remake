#ifndef MAINMENUHPP
#define MAINMENUHPP

#include <raylib.h>
#include <iostream>
#include "view.hpp"

namespace dv {
    class View;
    enum class GameState;


    class MainMenu {
        public:
            MainMenu() { this->init();};
            MainMenu(View* view) : view(view) { this->view = view; this->init();};

            ~MainMenu() {};
            void draw();
            void update();
        private:
            void init();
            void drawMain();
            void drawSettings();
            void updateMain();
            void updateSettings();

            View* view = nullptr;
            const Color BACKGROUND_COLOR = BLACK;
            const Color HOVER_COLOR = CLITERAL(Color){0x5F, 0x60, 0x61, 0x80};
            const Color TEXT_COLOR = WHITE;
            int menu_state = 0; // 0 = main, 1 = settings
            int wad_index = 0;
            int wad_count = 1;

            // Play button variables
            Rectangle playRec = { 190, 200, 200, 50 };
            Color playColor = this->BACKGROUND_COLOR;
            bool playAction = false;
            std::string playText = "Play";

            // Menu button variables
            Rectangle menuRec = { 190, 300, 200, 50 };
            Color menuColor = this->BACKGROUND_COLOR;
            bool menuAction = false;
            std::string menuText = "Menu";

            // Quit button variables
            Rectangle quitRec = { 190, 400, 200, 50 };
            Color quitColor = this->BACKGROUND_COLOR;
            bool quitAction = false;
            std::string quitText = "Quit";


            // Back button variables
            Rectangle backRec = { 190, 500, 200, 50 };
            Color backColor = this->BACKGROUND_COLOR;
            bool backAction = false;
            std::string backText = "Back";

            // WAD Loader Buttons
            Rectangle loadWADRec = { 190, 300, 200, 50 };
            Color loadWADColor = this->BACKGROUND_COLOR;
            bool loadWADAction = false;
            std::string loadWADText = "Load WAD";

            // WAD Selector Button
            Rectangle selectWADRec = { 240, 200, 200, 50 };
            Color selectWADColor = this->BACKGROUND_COLOR;
            bool selectWADAction = false;
            std::string selectWADText = "<WAD_Name>";

            // WAD Selector Arrow Buttons
            Rectangle leftArrowRec = { 190, 200, 50, 50 };
            Color leftArrowColor = this->BACKGROUND_COLOR;
            bool leftArrowAction = false;
            std::string leftArrowText = "<";
            Rectangle rightArrowRec = { 440, 200, 50, 50 };
            Color rightArrowColor = this->BACKGROUND_COLOR;
            bool rightArrowAction = false;
            std::string rightArrowText = ">";

            // Map Testing Button
            Rectangle mapTestRec = { 190, 400, 200, 50 };
            Color mapTestColor = this->BACKGROUND_COLOR;
            bool mapTestAction = false;
            std::string mapTestText = "Test Maps";
    };
};
#endif