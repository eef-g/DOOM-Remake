#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <vector>
#include <SFML/Graphics.hpp>

#include "components/ce_components.hpp"
using namespace CE_Components;

namespace CapulusEngine {
    class GameObject {
        private:
            // Variables
            std::vector<IComponent*> components;
        public:

            // Constructor
            GameObject();
            // Destructor
            virtual ~GameObject();

            // Functions
            void update(float frameTime);
            void render(sf::RenderTarget *target);
            void addComponent(IComponent *component);
            void removeComponent(IComponent *component);
            std::vector<IComponent*> getComponents() { return this->components; }
    };
}
#endif