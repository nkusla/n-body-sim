#include "../include/Solver.hpp"

void ForwardEuler::solve(std::vector<Body>& bodies, float dt) {
	for(Body& b : bodies) {
		b.addPosition(
			b.getVelocity() * dt
		);

		b.addVelocity(
			b.getAcceleration() * dt
		);
	}
}

void SemiImplicitEuler::solve(std::vector<Body>& bodies, float dt) {
	for(Body& b : bodies) {
		b.addVelocity(
			b.getAcceleration() * dt
		);

		b.addPosition(
			b.getVelocity() * dt
		);
	}
}

void Verlet::solve(std::vector<Body>& bodies, float dt) {

}