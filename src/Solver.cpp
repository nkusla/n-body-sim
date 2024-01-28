#include "../include/Solver.hpp"

void ImplicitEuler::solve(std::vector<Body>& bodies, float dt) {

}

void SemiImplicitEuler::solve(std::vector<Body>& bodies, float dt) {
	for(int i = 0; i < bodies.size(); i++) {
		bodies[i].addVelocity(
			bodies[i].getAcceleration() * dt
		);

		bodies[i].addPosition(
			bodies[i].getVelocity() * dt
		);

		for(int i = 0; i < bodies.size(); i++) {
			std::cout << bodies[i].getPosition().x << " " << bodies[i].getPosition().y << std::endl;
		}

		std::cout << std::endl;
	}
}

void VerletSolver::solve(std::vector<Body>& bodies, float dt) {

}