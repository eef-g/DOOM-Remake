#ifndef VIEW_HPP
#define VIEW_HPP

#include <raylib.h>
#include "../controller/controller.hpp"

namespace dv {
    class View {
    private:
        dc::Controller controller;
    public:
        View();
        void runGame();
    };
}

#endif