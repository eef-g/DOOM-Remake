#include "gameobject.hpp"

namespace CapulusEngine {
    GameObject::GameObject() {}

    GameObject::~GameObject() {
        for (auto &component : this->components) {
            delete component;
        }
    }

    void GameObject::update(float frameTime) {
        for (auto &component : this->components) {
            component->update(frameTime); // dereference the pointer to access the object
        }
    }

    void GameObject::render(sf::RenderTarget *target) {
        for (auto &component : this->components) {
            component->render(target); // dereference the pointer to access the object
        }
    }

    void GameObject::addComponent(IComponent *component) {
        this->components.insert(this->components.end(), component);
    }

    void GameObject::removeComponent(IComponent *component) {
        this->components.erase(std::remove(this->components.begin(), this->components.end(), component), this->components.end());
    }
}