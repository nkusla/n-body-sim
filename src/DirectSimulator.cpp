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
	glm::vec2 acc(0.f, 0.f);

	for(Body& b : bodies)
		b.setAcceleration({0.f, 0.f});

	for(int i = 0; i < bodies.size(); i++) {
		for(int j = i+1; j < bodies.size(); j++) {
			glm::vec2 r = bodies[i].getPosition() - bodies[j].getPosition();
			float r_div = glm::pow(glm::pow(r.length(), 2) + EPSILON*EPSILON, 1.5);

			r *= - G * bodies[j].getMass() / r_div;
			bodies[i].addAcceleration(r);
			bodies[j].addAcceleration(-r);
		}
	}
}

void DirectSimulator::simulate(float time_end) {
	for(float tick = 0.f; tick < time_end; tick += dt) {
		resultsLogger.startTimeMeasure();

		calculateBodyAcceleration();
		solver.solve(bodies, dt);

		resultsLogger.endTimeMeasure();
		resultsLogger.logSystemEnergy(bodies);
	}
}
