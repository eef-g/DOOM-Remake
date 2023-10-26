#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <iostream>
#include <SFML/Graphics.hpp>

/// @brief This is the class that will be inherited by all components
class Component {
    public:
        // Destructor
        virtual ~Component() {};

        // Functions
        virtual void update(float frameTime) = 0;
        virtual void render(sf::RenderTarget *target) = 0;
};
#endif