#include "testObj.hpp"
using namespace IsleGame;

TestObj::TestObj() {
    this->sprite = new Sprite("assets/character_single.png", sf::Vector2f(64.0f, 64.0f));
    this->hitbox = new Hitbox(
        sf::RectangleShape(sf::Vector2f(64.0f, 64.0f)),
        sf::Vector2f(0.0f, 0.0f),
        sf::Vector2f(64.0f, 64.0f),
        sf::Vector2f(0.0f, 0.0f),
        sf::Vector2f(1.0f, 1.0f)
    );

    this->addComponent(this->sprite);
    this->addComponent(this->hitbox);
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