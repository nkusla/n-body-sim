#include <iostream>
#include <random>

#include "../include/Solver.hpp"
#include "../include/Body.hpp"
#include "../include/DataParser.hpp"
#include "../include/DirectSimulator.hpp"
#include "../include/ApplicationWindow.hpp"

int main() {

	std::string csvDataPath = "../data/2_body.csv";
	std::string csvResultPath = "../results/result.csv";

	std::vector<Body> bodies;
	DataParser::readBodyDataFromCSV(csvDataPath, bodies);

	DirectSimulator directSimulator(bodies, STEP);
	directSimulator.setSolver(new SemiImplicitEuler());
	directSimulator.setSolver(new ForwardEuler());

	ApplicationWindow appWindow(1024, 768);

	while(appWindow.checkApplicationClose()) {
		appWindow.checKeyPressed();
		appWindow.displayBodies(bodies);
		directSimulator.simulateStep();

        glfwSwapBuffers(appWindow.getWindow());
        glfwPollEvents();
	}

	appWindow.closeApplication();

	DataParser::writeResultsDataToCSV(csvResultPath, directSimulator.getResultsLogger());

	return 0;
}