#include "GameObject.h"


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