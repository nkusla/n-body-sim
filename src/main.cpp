#include <iostream>
#include "../include/Solver.hpp"
#include "../include/Body.hpp"
#include "../include/DirectSimulator.hpp"

int main() {

	DirectSimulator sim(STEP, 2);

	Body b1(10e9f,
		{0.0f, 0.0f},
		{0.0f, 0.0f});

	Body b2 = b1;
	b2.setPosition({10.f, 10.f});

	std::vector<Body> bodies = {b1, b2};

	sim.setBodies(bodies);

	SemiImplicitEuler semiImplicitEuler;
	ForwardEuler forwardEuler;

	sim.simulate(10.f, semiImplicitEuler);

	return 0;
}