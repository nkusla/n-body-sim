#include "../include/Body.hpp"

Body::Body() :
	mass(0.0f),
	position({0.0f, 0.0f}),
	velocity({0.0f, 0.0f}),
	acceleration({0.0f, 0.0f})
	{}

Body::Body(float m, vector2 pos, vector2 vel, vector2 acc) :
	mass(m),
	position(pos),
	velocity(vel),
	acceleration(acc) {}

float Body::getMass() { return mass; }

vector2 Body::getPosition() { return position; }

vector2 Body::getVelocity() { return velocity; }

vector2 Body::getAcceleration() { return acceleration; }

void Body::setMass(float m) { mass = m; }

void Body::setPosition(vector2 pos) { position = pos; }

void Body::setVelocity(vector2 vel) { velocity = vel; }

void Body::setAcceleration(vector2 acc) { acceleration = acc; }

void Body::resetAcceleration() { acceleration = {0.0f, 0.0f}; }
