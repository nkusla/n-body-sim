#include "../include/ResultsLogger.hpp"

ResultsLogger::ResultsLogger() {}

std::vector<double>& ResultsLogger::getSystemEnergy() { return systemEnergy; }

std::vector<double>& ResultsLogger::getIterationExecutionTime() { return iterationExecutionTime; };

void ResultsLogger::startTimeMeasure() {
	startTime = std::chrono::high_resolution_clock::now();
}

void ResultsLogger::endTimeMeasure() {
	std::chrono::high_resolution_clock::time_point endTime = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double> timeSpan =
		std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

	iterationExecutionTime.push_back(timeSpan.count());
}

void ResultsLogger::resetLoggerData() {
	iterationExecutionTime.clear();
	systemEnergy.clear();
}

void ResultsLogger::logSystemEnergy(std::vector<Body>& bodies) {
	double kineticEnergy = 0.f;
	double potentialEnergy = 0.f;

	for(Body& b : bodies)
		kineticEnergy += 0.5 * b.getMass() * glm::pow(glm::length(b.getVelocity()), 2);

	for(int i = 0; i < bodies.size(); ++i) {
		for(int j = 0; j < bodies.size(); ++j) {
			if(i == j)
				continue;

			double r = glm::length(bodies[i].getPosition() - bodies[j].getPosition());
			potentialEnergy += - Globals::G * bodies[i].getMass() * bodies[j].getMass() / r;
		}
	}

	systemEnergy.push_back(kineticEnergy + potentialEnergy);
}