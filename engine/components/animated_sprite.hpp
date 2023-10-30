#ifndef ANIMATED_SPRITE_HPP
#define ANIMATED_SPRITE_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include "ce_components.hpp"


namespace CE_Components {
    class AnimatedSprite : public CE_Components::Sprite{
        private:
            // Variables
                // Animation Logic
            int animFrames = 0;
            float animTimer = 0.f;
            float frameTime =0.f;
        public:
            // Constructors
            AnimatedSprite();
            AnimatedSprite(std::string spritesheetPath, int rowCount, int colCount);
    };
}

#endif