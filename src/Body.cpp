#include "../include/Body.hpp"

Body::Body() :
	mass(0.0f),
	position(0.0f, 0.0f),
	velocity(0.0f, 0.0f),
	acceleration(0.0f, 0.0f)
	{}

Body::Body(float m, glm::vec2 pos, glm::vec2 vel) :
	mass(m),
	position(pos),
	velocity(vel) {}

float Body::getMass() { return mass; }

glm::vec2 Body::getPosition() { return position; }

glm::vec2 Body::getVelocity() { return velocity; }

glm::vec2 Body::getAcceleration() { return acceleration; }

void Body::setMass(float m) { mass = m; }

void Body::setPosition(glm::vec2 pos) { position = pos; }

void Body::setVelocity(glm::vec2 vel) { velocity = vel; }

void Body::setAcceleration(glm::vec2 acc) { acceleration = acc; }

void Body::addPosition(glm::vec2 pos) { position += pos; }

void Body::addAcceleration(glm::vec2 acc) { acceleration += acc; }

void Body::addVelocity(glm::vec2 vel) { velocity += vel; }