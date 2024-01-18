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

            View* view = nullptr;
            Image buttonBackground;
            Texture2D buttonTexture;
            Rectangle buttonRec;
            Color buttonColor;
            bool buttonAction = false;
            std::string buttonText = "Play";
    };
};
#endif