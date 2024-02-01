#include "../include/Simulator.hpp"

Simulator::Simulator(std::vector<Body>& bodies, float dt) :
	dt(dt),
	bodies(bodies),
	resultsLogger() {};

ResultsLogger& Simulator::getResultsLogger() { return resultsLogger; }

void Simulator::setDt(float dt) { dt = dt; }

void Simulator::setSolver(Solver* pSolver) {
	solver.reset(pSolver);
}

void Simulator::generateRandomBodies(float maxPos, float maxVel, float mass) {
	bodies.clear();

	std::default_random_engine generator(1616);
	std::uniform_real_distribution<float> posDist(-maxPos, maxPos);
	std::uniform_real_distribution<float> velDist(-maxVel, maxVel);

	for(int i = 0; i < N_BODIES; i++)
		bodies.push_back(
			Body(mass,
			{posDist(generator), posDist(generator)},
			{velDist(generator), velDist(generator)})
		);
}

void Simulator::simulate(float timeEnd) {
	for(float tick = 0.f; tick < timeEnd; tick += dt) {
		simulateStep();
	}
}