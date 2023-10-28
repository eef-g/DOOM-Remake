#ifndef TESTOBJ_HPP
#define TESTOBJ_HPP

#include "IsleGame.hpp"

namespace IsleGame {
    class TestObj : public GameObject {
        private:
            // Variables
        // Sprite *sprite;
        // Hitbox *hitbox;
        PlayerController *controller;

        public:
            // Constructor
            TestObj();
            // Destructor
            virtual ~TestObj() override;

            // Functions
            void update(float frameTime);
            void render(sf::RenderTarget *target);      
    };
}
#endif