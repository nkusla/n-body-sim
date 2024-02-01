#include "../include/BarnesHutSimulator.hpp"

BarnesHutSimulator::BarnesHutSimulator(std::vector<Body>& bodies, float dt, float rootRegionWidth, float theta)
: Simulator(bodies, dt), theta(theta) {
	root = new QuadtreeNode(
		{-rootRegionWidth/2, rootRegionWidth/2},
		{rootRegionWidth/2, -rootRegionWidth/2}
	);
}

BarnesHutSimulator::~BarnesHutSimulator() {
	root->~QuadtreeNode();
	delete root;
}

void BarnesHutSimulator::constructQuadtree(std::vector<Body>& bodies) {
	for(Body& b : bodies)
		root->recursivelyInsertBody(b);
}

void BarnesHutSimulator::simulateStep() {
	// resultsLogger.startTimeMeasure();

	// solver->solve(bodies, dt);

	// resultsLogger.endTimeMeasure();
	// resultsLogger.logSystemEnergy(bodies);
}