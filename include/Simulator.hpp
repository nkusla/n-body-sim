#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <vector>
#include <random>
#include <memory>

#include "Body.hpp"
#include "Solver.hpp"
#include "ResultsLogger.hpp"
#include "params.hpp"

class Simulator {
	protected:
		float dt;
		std::vector<Body>& bodies;
		std::unique_ptr<Solver> solver;
		ResultsLogger resultsLogger;

	public:
		Simulator(std::vector<Body>& bodies, float dt);

		ResultsLogger& getResultsLogger();
		void setDt(float dt);
		void setSolver(Solver* solver);
		void generateRandomBodies(float maxPos, float maxVel, float mass);

		void simulate(float timeEnd);
		virtual void simulateStep() = 0;
};

#endif