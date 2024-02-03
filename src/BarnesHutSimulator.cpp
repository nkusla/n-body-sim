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
		{rootRegionHalfWidth, -rootRegionHalfWidth},
		-1, bodies
	);

	for(int i = 0; i < bodies.size(); i++)
		root->recursivelyInsertBody(i);
}

void BarnesHutSimulator::destroyQuadtree() {
	delete root;
	root = nullptr;
}

void BarnesHutSimulator::calculateBodyAcceleration() {
	for(int i = 0; i < bodies.size(); i++) {
		bodies[i].setAcceleration({0.f, 0.f});
		root->recursivelyCalculateBodyAcceleration(i);
	}
}

void BarnesHutSimulator::simulateStep() {
	time += dt;
	resultsLogger.startTimeMeasure();

	constructQuadtree();
	calculateBodyAcceleration();
	solver->solve(bodies, dt);
	destroyQuadtree();

	resultsLogger.endTimeMeasure();
	resultsLogger.logSystemEnergy(bodies);
}