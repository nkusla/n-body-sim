#include "../include/Simulator.hpp"

Simulator::Simulator(std::vector<Body>& bodies, float dt) :
	dt(dt),
	bodies(bodies),
	elapsedTime(0.0f),
	resultsLogger() {};

ResultsLogger& Simulator::getResultsLogger() { return resultsLogger; }

void Simulator::setDt(float dt) { dt = dt; }

void Simulator::setSolver(std::shared_ptr<Solver> pSolver) {
	solver = pSolver;
}

std::vector<Body>& Simulator::getBodies() {
	return bodies;
}

float Simulator::getElapsedTime() { return elapsedTime; }

void Simulator::generateRandomBodies(float maxPos, float maxVel, float mass) {
	bodies.clear();

	std::chrono::system_clock::time_point tp = std::chrono::system_clock::now();
	long long seed = std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch()).count();

	std::default_random_engine generator(1616);
	std::uniform_real_distribution<float> posDist(-maxPos, maxPos);
	std::uniform_real_distribution<float> velDist(-maxVel, maxVel);

	for(int i = 0; i < Globals::N_RANDOM_BODIES; i++)
		bodies.push_back(
			Body(mass,
			{posDist(generator), posDist(generator)},
			{velDist(generator), velDist(generator)})
		);
}

void Simulator::resetSimulation() {
	elapsedTime = 0.f;
	resultsLogger.resetLoggerData();
}

void Simulator::simulate(float timeEnd) {
	for(float tick = 0.f; tick < timeEnd; tick += dt) {
		simulateStep();
	}
}