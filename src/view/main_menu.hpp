#ifndef MAINMENUHPP
#define MAINMENUHPP

#include <raylib.h>

#include <raygui.h>
#include <iostream>

namespace dv {
    class MainMenu {
        public:
            MainMenu();
            ~MainMenu();
            void draw();
            void update();
        private:
            int dropDownBoxState;
    };
};
#endif