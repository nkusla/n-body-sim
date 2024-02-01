#ifndef SOLVER_H
#define SOLVER_H

#include "params.hpp"
#include "Body.hpp"
#include <vector>

class Solver {
	public:
		void calculateBodyAcceleration(std::vector<Body>& bodies);
		float calculateDistanceEpsilon(glm::vec2 r);
		float calculateDistanceMax(glm::vec2 r);
		virtual void solve(std::vector<Body>& bodies, float dt) {}
};

class ForwardEuler : public Solver {
	public:
		void solve(std::vector<Body>& bodies, float dt);
};

class SemiImplicitEuler : public Solver {
	public:
		void solve(std::vector<Body>& bodies, float dt);
};

class Verlet : public Solver {
	public:
		void solve(std::vector<Body>& bodies, float dt);
};

#endif