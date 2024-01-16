#ifndef VIEW_HPP
#define VIEW_HPP

#include <raylib.h>
#include "../controller/controller.hpp"

namespace dv {
    class View {
    private:
        dc::Controller *controller = nullptr;
    public:
        View();
        ~View() { delete this->controller; };
        void runGame();
    };
}

#endif