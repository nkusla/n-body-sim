#include <iostream>
#include <random>

#include "../include/Solver.hpp"
#include "../include/Body.hpp"
#include "../include/DataParser.hpp"
#include "../include/DirectSimulator.hpp"
#include "../include/ApplicationWindow.hpp"
#include "../include/BarnesHutSimulator.hpp"

int main() {

	std::string csvResultPath = "../results/result.csv";
	std::vector<Body> bodies;

	ApplicationWindow::simulators = {
		std::make_shared<DirectSimulator>(bodies, STEP),
		std::make_shared<BarnesHutSimulator>(bodies, STEP, GLOBAL_QUADRANT_SIZE, THETA)
	};

	ApplicationWindow::solvers = {
		std::make_shared<SemiImplicitEuler>(),
		std::make_shared<ForwardEuler>(),
		std::make_shared<Verlet>()
	};

	ApplicationWindow appWindow(1366, 768);
	appWindow.resetSimulator();

	while(appWindow.checkApplicationClose()) {
		appWindow.checKeyPressed();

		appWindow.runFrame();
	}

	appWindow.closeApplication();

	DataParser::writeResultsDataToCSV(csvResultPath, appWindow.getSimulator()->getResultsLogger());

	return 0;
}