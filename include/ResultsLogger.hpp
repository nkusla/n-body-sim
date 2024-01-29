#ifndef RESULTS_LOGGER_H
#define RESULTS_LOGGER_H

#include <vector>
#include <chrono>
#include "Body.hpp"
#include "params.hpp"

class ResultsLogger {
	private:
		std::vector<float> systemEnergy;
		std::vector<float> iterationExecutionTime;
		std::chrono::high_resolution_clock::time_point startTime;

	public:
		ResultsLogger();
		std::vector<float>& getSystemEnergy();
		std::vector<float>& getIterationExecutionTime();

		void startTimeMeasure();
		void endTimeMeasure();
		void resetLoggerData();
		void logSystemEnergy(std::vector<Body>& bodies);
};

#endif