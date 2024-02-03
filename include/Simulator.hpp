#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <vector>
#include <random>
#include <memory>

#include "Body.hpp"
#include "Solver.hpp"
#include "ResultsLogger.hpp"
#include "Globals.hpp"

class Simulator {
	protected:
		float dt;
		std::vector<Body>& bodies;
		std::shared_ptr<Solver> solver;
		ResultsLogger resultsLogger;
		float elapsedTime;

	public:
		Simulator(std::vector<Body>& bodies, float dt);

		ResultsLogger& getResultsLogger();
		void setDt(float dt);
		void setSolver(std::shared_ptr<Solver> pSolver);
		std::vector<Body>& getBodies();
		float getElapsedTime();
		void generateRandomBodies(float maxPos, float maxVel, float mass);

		void resetSimulation();
		void simulate(float timeEnd);
		virtual void simulateStep() = 0;
};

#endif