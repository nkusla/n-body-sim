#ifndef SOLVER_H
#define SOLVER_H

#include "Body.hpp"
#include <vector>
#include <iostream>

class Solver {
	public:
		virtual void solve(std::vector<Body>& bodies, float dt) {}
};

class ImplicitEuler : public Solver {
	public:
		void solve(std::vector<Body>& bodies, float dt);
};

class SemiImplicitEuler : public Solver {
	public:
		void solve(std::vector<Body>& bodies, float dt);
};

class VerletSolver : public Solver {
	public:
		void solve(std::vector<Body>& bodies, float dt);
};

#endif