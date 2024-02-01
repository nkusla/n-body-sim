#ifndef DIRECT_H
#define DIRECT_H

#include <cmath>
#include <vector>
#include <iostream>
#include <random>

#include "Body.hpp"
#include "Solver.hpp"
#include "ResultsLogger.hpp"
#include "params.hpp"


class DirectSimulator {
	private:
		float dt;
		std::vector<Body>& bodies;
		Solver& solver;
		ResultsLogger resultsLogger;

	public:
		DirectSimulator(float dt, std::vector<Body>& bodies, Solver& solver);

		ResultsLogger& getResultsLogger();
		void setDt(float dt);
		void setSolver(Solver& solver);
		void generateRandomBodies();

		void simulate(float time);
		void simulateStep();
};


#endif