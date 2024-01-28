#ifndef DIRECT_H
#define DIRECT_H

#include "Body.hpp"
#include "Solver.hpp"
#include "params.hpp"
#include <cmath>
#include <vector>

class DirectSimulator {
	private:
		float dt;
		std::vector<Body> bodies;

	public:
		DirectSimulator();
		DirectSimulator(float dt, int num_bodies);

		void setDt(float dt);
		void setBodies(std::vector<Body> b);

		void calculateBodyAcceleration();
		void simulate(float time, Solver& solver);
};


#endif