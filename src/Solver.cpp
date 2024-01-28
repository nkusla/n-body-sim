#include "../include/Solver.hpp"

void ForwardEuler::solve(std::vector<Body>& bodies, float dt) {
	for(int i = 0; i < bodies.size(); i++) {
		bodies[i].addPosition(
			bodies[i].getVelocity() * dt
		);

		bodies[i].addVelocity(
			bodies[i].getAcceleration() * dt
		);
	}
}

void SemiImplicitEuler::solve(std::vector<Body>& bodies, float dt) {
	for(int i = 0; i < bodies.size(); i++) {
		bodies[i].addVelocity(
			bodies[i].getAcceleration() * dt
		);

		bodies[i].addPosition(
			bodies[i].getVelocity() * dt
		);
	}
}

void Verlet::solve(std::vector<Body>& bodies, float dt) {

}