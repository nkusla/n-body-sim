#ifndef BARNES_HUT_SIMULATOR_H
#define BARNES_HUT_SIMULATOR_H

#include "Simulator.hpp"
#include "QuadtreeNode.hpp"

class BarnesHutSimulator : public Simulator {
	private:
		QuadtreeNode* root;
		float theta;

	public:
		BarnesHutSimulator(std::vector<Body>& bodies, float dt, float rootRegionWidth, float theta);
		~BarnesHutSimulator();

		void constructQuadtree(std::vector<Body>& bodies);
		void simulateStep();
};

#endif