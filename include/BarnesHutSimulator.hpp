#ifndef BARNES_HUT_SIMULATOR_H
#define BARNES_HUT_SIMULATOR_H

#include "Simulator.hpp"
#include "QuadtreeNode.hpp"

class BarnesHutSimulator : public Simulator {
	private:
		QuadtreeNode* root;
		float rootRegionHalfWidth;

	public:
		BarnesHutSimulator(std::vector<Body>& bodies, float dt, float rootRegionHalfWidth);
		~BarnesHutSimulator();

		void constructQuadtree();
		void destroyQuadtree();
		void calculateBodyAcceleration();
		void simulateStep();
};

#endif