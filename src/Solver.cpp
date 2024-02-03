#include "../include/Solver.hpp"

void ForwardEuler::solve(std::vector<Body>& bodies, float dt) {
	for(Body& b : bodies) {
		b.addPosition(b.getVelocity() * dt);

		b.addVelocity(b.getAcceleration() * dt);
	}
}

void SemiImplicitEuler::solve(std::vector<Body>& bodies, float dt) {
	for(Body& b : bodies) {
		b.addVelocity(b.getAcceleration() * dt);

		b.addPosition(b.getVelocity() * dt);
	}
}

void Verlet::initSolver(std::vector<Body>& bodies, float dt) {
	float dt_2 = 0.5 * dt * dt;

	previousPosition.clear();
	for(Body& b : bodies) {
		previousPosition.push_back(b.getPosition());
		b.addPosition(b.getVelocity() * dt + b.getAcceleration() * dt_2);
	}
}

void Verlet::solve(std::vector<Body>& bodies, float dt) {
	for(int i = 0; i < bodies.size(); i++) {
		glm::vec2 newPosition = bodies[i].getPosition();
		newPosition *= 2;
		newPosition -= previousPosition[i];
		newPosition += bodies[i].getAcceleration() * dt * dt;

		previousPosition[i] = bodies[i].getPosition();
		bodies[i].setPosition(newPosition);
	}
}