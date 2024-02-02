#include "../include/BarnesHutSimulator.hpp"

BarnesHutSimulator::BarnesHutSimulator(std::vector<Body>& bodies, float dt, float rootRegionHalfWidth, float theta) :
	Simulator(bodies, dt),
	rootRegionHalfWidth(rootRegionHalfWidth),
	theta(theta) {}

BarnesHutSimulator::~BarnesHutSimulator() {
	destroyQuadtree();
}

void BarnesHutSimulator::constructQuadtree() {
	root = new QuadtreeNode(
		{-rootRegionHalfWidth, rootRegionHalfWidth},
		{rootRegionHalfWidth, -rootRegionHalfWidth}
	);

	for(int i = 0; i < bodies.size(); i++)
		root->recursivelyInsertBody(bodies[i], i);
}

void BarnesHutSimulator::destroyQuadtree() {
	if(root != nullptr)
		delete root;
}

void BarnesHutSimulator::calculateBodyAcceleration() {
	for(int i = 0; i < bodies.size(); i++) {
		bodies[i].setAcceleration({0.f, 0.f});
		root->recursivelyCalculateBodyAcceleration(bodies[i], i, theta);
	}
}

void BarnesHutSimulator::simulateStep() {
	resultsLogger.startTimeMeasure();

	constructQuadtree();
	calculateBodyAcceleration();
	solver->solve(bodies, dt);
	destroyQuadtree();

	resultsLogger.endTimeMeasure();
	resultsLogger.logSystemEnergy(bodies);
}