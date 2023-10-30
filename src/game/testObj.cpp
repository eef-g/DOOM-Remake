#include "testObj.hpp"
using namespace IsleGame;

TestObj::TestObj() {
    // Create the playerController component
    this->controller = new PlayerController("assets/character_single.png", sf::Vector2f(64.0f, 64.0f));
    this->controller->setOffset(-2.0f, -1.0f);

    // Add all the compopnents to the game object
    this->addComponent(this->controller);
}

TestObj::~TestObj() {
    for(auto component : this->getComponents()) {
        delete component;
    }
}

void TestObj::update(float frameTime) {
    this->GameObject::update(frameTime);
}

void TestObj::render(sf::RenderTarget *target) {
    this->GameObject::render(target);
}