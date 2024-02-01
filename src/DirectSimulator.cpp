#include "../include/DirectSimulator.hpp"

DirectSimulator::DirectSimulator(float dt, std::vector<Body>& bodies, Solver& solver)
	: dt(dt),
	bodies(bodies),
	solver(solver),
	resultsLogger() {};

ResultsLogger& DirectSimulator::getResultsLogger() { return resultsLogger; }

void DirectSimulator::setDt(float dt) { dt = dt; }

void DirectSimulator::setSolver(Solver& solver) { solver = solver; }

void DirectSimulator::generateRandomBodies() {
	bodies.clear();

	std::default_random_engine generator(1616);
	std::uniform_real_distribution<float> posDist(-1e3, 1e3);
	std::uniform_real_distribution<float> velDist(-1e3, 1e3);
	std::uniform_real_distribution<float> massDist(1e9, 1e10);

	for(int i = 0; i < N_BODIES; i++)
		bodies.push_back(
			Body(massDist(generator),
			{posDist(generator), posDist(generator)},
			{velDist(generator), velDist(generator)})
		);
}

void DirectSimulator::simulate(float time_end) {
	for(float tick = 0.f; tick < time_end; tick += dt) {
		simulateStep();
	}
}

void DirectSimulator::simulateStep() {
	resultsLogger.startTimeMeasure();

	solver.calculateBodyAcceleration(bodies);
	solver.solve(bodies, dt);

	resultsLogger.endTimeMeasure();
	resultsLogger.logSystemEnergy(bodies);
}