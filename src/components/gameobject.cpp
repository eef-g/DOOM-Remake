#include "gameobject.hpp"

GameObject::GameObject() {

}

GameObject::~GameObject() {

}

void GameObject::update(float frameTime) {
    for (auto &component : this->components) {
        component.second->update(frameTime); // dereference the pointer to access the object
    }
}

void GameObject::render(sf::RenderTarget *target) {
    for (auto &component : this->components) {
        component.second->render(target); // dereference the pointer to access the object
    }
}

void GameObject::addComponent(Component *component) {
    this->components.insert(std::make_pair(this->componentCount++, component));
}