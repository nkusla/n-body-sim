#include <iostream>
#include "../include/Solver.hpp"
#include "../include/Body.hpp"
#include "../include/DirectSimulator.hpp"

int main() {

	DirectSimulator sim(0.01, 2);

	Body b1(10e9f,
		{0.0f, 0.0f},
		{0.0f, 0.0f});

	Body b2 = b1;
	b2.setPosition({10.f, 10.f});

	std::vector<Body> bodies = {b1, b2};

	sim.setBodies(bodies);

	SemiImplicitEuler sme = SemiImplicitEuler();

	sim.simulate(5.f, sme);

	return 0;
}