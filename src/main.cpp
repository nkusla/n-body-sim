#include <iostream>
#include <random>

#include "../include/Solver.hpp"
#include "../include/Body.hpp"
#include "../include/DataParser.hpp"
#include "../include/DirectSimulator.hpp"
#include "../include/ApplicationWindow.hpp"

int main() {

	// std::string csvDataPath = "../data/2_body.csv";
	// std::string csvResultPath = "../results/result.csv";

	// ForwardEuler forwardEuler = ForwardEuler();
	// SemiImplicitEuler semiImplicitEuler = SemiImplicitEuler();
	// Verlet verlet = Verlet();

	// std::vector<Body> bodies;
	// DataParser::readBodyDataFromCSV(csvDataPath, bodies);

	// DirectSimulator directSimulator(STEP, bodies, semiImplicitEuler);

	ApplicationWindow appWindow(1024, 768);

	while(appWindow.checkApplicationClose()) {
		// Swap front and back buffers
        //glfwSwapBuffers(appWindow.getWindow());

        // Poll for and process events
        glfwPollEvents();
	}

	appWindow.closeApplication();

	//DataParser::writeResultsDataToCSV(csvResultPath, directSimulator.getResultsLogger());

	return 0;
}