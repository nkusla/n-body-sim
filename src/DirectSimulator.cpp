#include "../include/DirectSimulator.hpp"

DirectSimulator::DirectSimulator(std::vector<Body>& bodies, float dt) :
	Simulator(bodies, dt) {}

float DirectSimulator::calculateDistanceWitSoftening(glm::vec2 r) {
	return glm::pow(
		glm::pow(glm::length(r), 2) + EPSILON*EPSILON, 1.5);
}

float DirectSimulator::calculateDistanceWithMaxCut(glm::vec2 r) {
	float r_mag = glm::max(0.8f, glm::length(r));
	return glm::pow(r_mag, 3);
}

void DirectSimulator::calculateBodyAcceleration() {
	for(Body& b : bodies)
		b.setAcceleration({0.f, 0.f});

	for(int i = 0; i < bodies.size(); i++) {
		for(int j = i+1; j < bodies.size(); j++) {

			glm::vec2 r = bodies[i].getPosition() - bodies[j].getPosition();
			float r_div = calculateDistanceWithMaxCut(r);

			r *= - G / r_div;
			glm::vec2 acc_i = r * bodies[j].getMass();
			glm::vec2 acc_j = - r * bodies[i].getMass();

			bodies[i].addAcceleration(acc_i);
			bodies[j].addAcceleration(acc_j);
		}
	}
}

void DirectSimulator::simulateStep() {
	resultsLogger.startTimeMeasure();

	calculateBodyAcceleration();
	solver->solve(bodies, dt);

	resultsLogger.endTimeMeasure();
	resultsLogger.logSystemEnergy(bodies);
	elapsedTime += dt;
}