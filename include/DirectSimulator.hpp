#ifndef DIRECT_H
#define DIRECT_H

#include <vector>

#include "Simulator.hpp"

class DirectSimulator : public Simulator {

	public:
		DirectSimulator(std::vector<Body>& bodies, float dt);

		float calculateDistanceWitSoftening(glm::vec2 r);
		float calculateDistanceWithMaxCut(glm::vec2 r);
		void calculateBodyAcceleration();
		void simulateStep();
};


#endif