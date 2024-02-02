#include <iostream>
#include <random>

#include "../include/Solver.hpp"
#include "../include/Body.hpp"
#include "../include/DataParser.hpp"
#include "../include/DirectSimulator.hpp"
#include "../include/ApplicationWindow.hpp"

int main() {

	std::string csvResultPath = "../results/result.csv";
	std::vector<Body> bodies;

	std::shared_ptr<DirectSimulator> directSimulator(new DirectSimulator(bodies, STEP));
	directSimulator->setSolver(std::make_shared<SemiImplicitEuler>());

	ApplicationWindow appWindow(1366, 768);
	appWindow.setSimulator(directSimulator);
	appWindow.resetSimulator();

	// while(glfwGetKey(appWindow.getWindow(), GLFW_KEY_SPACE) != GLFW_PRESS)
	// 	glfwPollEvents();

	while(appWindow.checkApplicationClose()) {
		appWindow.checKeyPressed();

		appWindow.runFrame();
	}

	appWindow.closeApplication();

	DataParser::writeResultsDataToCSV(csvResultPath, directSimulator->getResultsLogger());

	return 0;
}