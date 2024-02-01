#include "../include/DirectSimulator.hpp"

DirectSimulator::DirectSimulator(float dt, std::vector<Body>& bodies, Solver& solver)
	: dt(dt),
	bodies(bodies),
	solver(solver),
	resultsLogger() {};

ResultsLogger& DirectSimulator::getResultsLogger() { return resultsLogger; }

void DirectSimulator::setDt(float dt) { dt = dt; }

void DirectSimulator::setSolver(Solver& solver) { solver = solver; }

void DirectSimulator::setBodies(std::vector<Body>& b) { bodies = b; }

void DirectSimulator::calculateBodyAcceleration() {

	for(Body& b : bodies)
		b.setAcceleration({0.f, 0.f});

	for(int i = 0; i < bodies.size(); i++) {
		for(int j = i+1; j < bodies.size(); j++) {

			glm::vec2 r = bodies[i].getPosition() - bodies[j].getPosition();
			float r_div = glm::pow(glm::pow(r.length(), 2) + EPSILON*EPSILON, 1.5);

			r *= - G / r_div;
			glm::vec2 acc_i = r * bodies[j].getMass();
			glm::vec2 acc_j = - r * bodies[i].getMass();

			bodies[i].addAcceleration(acc_i);
			bodies[j].addAcceleration(acc_j);
		}
	}
}

void DirectSimulator::simulate(float time_end) {
	for(float tick = 0.f; tick < time_end; tick += dt) {
		simulateStep();
	}
}

void DirectSimulator::simulateStep() {
	resultsLogger.startTimeMeasure();

	calculateBodyAcceleration();
	solver.solve(bodies, dt);

	resultsLogger.endTimeMeasure();
	resultsLogger.logSystemEnergy(bodies);
}