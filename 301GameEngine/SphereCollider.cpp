#include "SphereCollider.h"

SphereCollider::SphereCollider(glm::vec3 * position, float radii) {
	this->colliderCentre = position;
	this->sphereRadius = radii;
}

float SphereCollider::X() {
	return this->colliderCentre->x;
}

float SphereCollider::Y() {
	return this->colliderCentre->y;
}

float SphereCollider::Z() {
	return this->colliderCentre->z;
}

SphereCollider::~SphereCollider() {
}

bool SphereCollider::collidesWith(Collider* other) {
	if (other == NULL) {
		return false;
	}
	float distanceX = this->X() - other->X();
	float distanceY = this->Y() - other->Y();
	float distanceZ = this->Z() - other->Z();

	return distanceX + distanceY + distanceZ <= sphereRadius;
}

//Draw cube ith vertices so that we can show it in debug mode.
 void SphereCollider::Draw() 
{

}
