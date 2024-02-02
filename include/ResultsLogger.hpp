#ifndef RESULTS_LOGGER_H
#define RESULTS_LOGGER_H

#include <vector>
#include <chrono>
#include "Body.hpp"
#include "globals.hpp"

class ResultsLogger {
	private:
		std::vector<double> systemEnergy;
		std::vector<double> iterationExecutionTime;
		std::chrono::high_resolution_clock::time_point startTime;

	public:
		ResultsLogger();
		std::vector<double>& getSystemEnergy();
		std::vector<double>& getIterationExecutionTime();

		void startTimeMeasure();
		void endTimeMeasure();
		void resetLoggerData();
		void logSystemEnergy(std::vector<Body>& bodies);
};

#endif