#include "../include/DirectSimulator.hpp"

DirectSimulator::DirectSimulator() {}

DirectSimulator::DirectSimulator(float dt, int num_bodies) : dt(dt), bodies(num_bodies) {};

void DirectSimulator::setDt(float dt) { dt = dt; }

void DirectSimulator::setBodies(std::vector<Body> b) { bodies = b; }

void DirectSimulator::calculateBodyAcceleration() {
	glm::vec2 acc(0.f, 0.f);

	for(int i = 0; i < bodies.size(); i++)
		bodies[i].setAcceleration({0.f, 0.f});

	for(int i = 0; i < bodies.size(); i++) {
		for(int j = 0; j < bodies.size(); j++) {
			if (i == j)
				continue;

			glm::vec2 r = bodies[i].getPosition() - bodies[j].getPosition();
			float r_div = glm::pow(glm::pow(r.length(), 2) + EPSILON*EPSILON, 1.5);

			r *= - G * bodies[j].getMass() / r_div;
			bodies[i].addAcceleration(r);
		}
	}
}

void DirectSimulator::simulate(float time_end, Solver& solver) {
	for(float tick = 0.f; tick < time_end; tick += dt) {
		calculateBodyAcceleration();
		solver.solve(bodies, dt);

		// for(int i = 0; i < bodies.size(); i++) {
		// 	std::cout << bodies[i].getPosition().x << " " << bodies[i].getPosition().y << std::endl;
		// }

		// std::cout << std::endl;
	}
}
