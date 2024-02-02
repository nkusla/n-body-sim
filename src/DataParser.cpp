#include "../include/DataParser.hpp"

void DataParser::readBodyDataFromCSV(std::string csvPath, std::vector<Body>& bodies) {
	std::ifstream file(csvPath);

	if(!file.is_open()) {
		std::cout << "Error opening file!" << std::endl;
		return;
	}

	bodies.clear();
	std::string line;
	std::string field;
	std::vector<float> data;
	std::getline(file, line); // skipping header

	while(std::getline(file, line)) {
		std::stringstream lineStream(line);

		data.clear();
		while(std::getline(lineStream, field, ',')) {
			data.push_back(std::stof(field));
		}

		bodies.push_back(Body(data[0],
			glm::vec2(data[1], data[2]),
			glm::vec2(data[3], data[4])));
	}

	file.close();
}

void DataParser::writeResultsDataToCSV(std::string csvPath, ResultsLogger& resultsLogger) {
	std::ofstream file(csvPath);

	if(!file.is_open()) {
		std::cout << "Error opening file!" << std::endl;
		return;
	}

	file << "iterTime,totalEnergy" << std::endl;
	std::string line;

	std::vector<double>& systemEnergy = resultsLogger.getSystemEnergy();
	std::vector<double>& iterationExecutionTime = resultsLogger.getIterationExecutionTime();

	for(int i = 0; i < systemEnergy.size(); ++i)
		file << iterationExecutionTime[i] << "," << systemEnergy[i] << std::endl;

	file.close();
}

void DataParser::writeBodyDataToCSV(std::string csvPath, std::vector<Body>& bodies) {
	std::ofstream file(csvPath);

	if(!file.is_open()) {
		std::cout << "Error opening file!" << std::endl;
		return;
	}

	file << "mass,x,y,vx,vy" << std::endl;

	for(Body& b : bodies) {
		file << b.getMass() << ","
		<< b.getPosition().x << "," << b.getPosition().y << ","
		<< b.getVelocity().x << "," << b.getVelocity().y << std::endl;
	}

	file.close();
}