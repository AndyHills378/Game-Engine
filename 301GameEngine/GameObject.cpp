#include "GameObject.h"

bool GameObject::debugMode;
std::map <int, bool> specialKeys;
std::map <char, bool> keys;


GameObject::GameObject(glm::vec3 pos) {
	this->position = pos;
}


GameObject::~GameObject() {
}

void GameObject::drawScene() {

}
void GameObject::setupDrawing() {

}
void GameObject::collides(Collider* other) {
}