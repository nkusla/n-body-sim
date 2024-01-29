#ifndef DATA_PARSER_H
#define DATA_PARSER_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "Body.hpp"
#include "ResultsLogger.hpp"

class DataParser {
	public:
		static void readBodyDataFromCSV(std::string csvPath, std::vector<Body>& bodies);
		static void writeResultsDataToCSV(std::string csvPath, ResultsLogger& resultsLogger);
};

#endif