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

            ~MapTest() {this->view = nullptr;};
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
            bool mapLoaded = false;

            // Back button variables -- Placed in top-right corner
            Rectangle backRec = { 1500, 25, 200, 50 };
            Color backColor = this->BACKGROUND_COLOR;
            std::string backText = "Back";

            // Map title -- Placed in top-center
            Rectangle mapTitleRec = { 700, 50, 200, 50 };
            Color mapTitleColor = this->BACKGROUND_COLOR;
            // TODO: Replace with dynamically changing map name
            std::string mapTitleText = "E1M1";

            // Load Button -- Placed below the map title
            Rectangle loadRec = { 700, 125, 200, 50 };
            Color loadColor = this->BACKGROUND_COLOR;
            std::string loadText = "Load";

            // Left & Right Arrows -- Placed on the sides of the load button
            Rectangle leftArrowRec = { 650, 125, 50, 50 };
            Color leftArrowColor = this->BACKGROUND_COLOR;
            std::string leftArrowText = "<";
            Rectangle rightArrowRec = { 900, 125, 50, 50 };
            Color rightArrowColor = this->BACKGROUND_COLOR;
            std::string rightArrowText = ">";
    };
}
#endif