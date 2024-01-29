#include <iostream>
#include <random>
#include <GLFW/glfw3.h>
#include <GL/gl.h>

#include "../include/Solver.hpp"
#include "../include/Body.hpp"
#include "../include/DataParser.hpp"
#include "../include/DirectSimulator.hpp"

int main() {

	std::string csvDataPath = "../data/2_body.csv";
	std::string csvResultPath = "../results/result.csv";

	ForwardEuler forwardEuler = ForwardEuler();
	SemiImplicitEuler semiImplicitEuler = SemiImplicitEuler();
	Verlet verlet = Verlet();

	std::vector<Body> bodies;
	DataParser::readBodyDataFromCSV(csvDataPath, bodies);

	DirectSimulator directSimulator(STEP, bodies, semiImplicitEuler);
	directSimulator.simulate(5.0);

	DataParser::writeResultsDataToCSV(csvResultPath, directSimulator.getResultsLogger());

	return 0;
}