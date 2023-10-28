#ifndef CE_COMPONENT_HPP
#define CE_COMPONENT_HPP

#include <iostream>
#include <SFML/Graphics.hpp>

namespace CE_Components{
    /// @brief This is the class that will be inherited by all components
    class IComponent {
        public:
            // Destructor
            virtual ~IComponent() {};

            // Functions
            virtual void update(float frameTime) = 0;
            virtual void render(sf::RenderTarget *target) = 0;
    };
}

#endif