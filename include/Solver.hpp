#ifndef SOLVER_H
#define SOLVER_H

class Solver {
	virtual void solve() = 0;
};

class ForwardEulerSolver : public Solver {
	public:
		void solve();
};

class BackwardEulerSolver : public Solver {
	public:
		void solve();
};

class VerletSolver : public Solver {
	public:
		void solve();
};

#endif