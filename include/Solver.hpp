#ifndef SOLVER_H
#define SOLVER_H

#include "globals.hpp"
#include "Body.hpp"
#include <vector>

class Solver {
	public:
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