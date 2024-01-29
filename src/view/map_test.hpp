#ifndef MAPTEST_HPP
#define MAPTEST_HPP

#include <raylib.h>
#include <iostream>
#include "view.hpp"

namespace dv {
    class View;
    enum class GameState;

    class MapTest {
        public:
            MapTest() { this->init();};
            MapTest(View* view) : view(view) { this->view = view; this->init();};

            ~MapTest() {};
            void draw();
            void update();
        private:
            void init();
            void drawMap();
            void drawSettings();
            void updateMap();
            void updateSettings();

            View* view = nullptr;
            const Color BACKGROUND_COLOR = BLACK;
            const Color HOVER_COLOR = CLITERAL(Color){0x5F, 0x60, 0x61, 0x80};
            const Color TEXT_COLOR = WHITE;

            // Back button variables
            Rectangle backRec = { 190, 400, 200, 50 };
            Color backColor = this->BACKGROUND_COLOR;
            std::string quitText = "Back";
    };
}


#endif