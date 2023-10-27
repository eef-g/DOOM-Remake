#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP


#include "component.hpp"
#include "hitbox.hpp"


#include <iostream>
#include <SFML/Graphics.hpp>
#include <unordered_map>

class GameObject {
    private:
        // Variables
        std::unordered_map<int, Component*> components;
        int componentCount = 0;
    public:

        // Constructor
        GameObject();
        // Destructor
        virtual ~GameObject();

        // Functions
        void update(float frameTime);
        void render(sf::RenderTarget *target);
        void addComponent(Component *component);
};

#endif