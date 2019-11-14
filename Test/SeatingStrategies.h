#pragma once
#include "Passenger.h"

#include <chrono>
#include <random>
#include <vector>
using std::vector;

class SeatingStrategies {
public:
	void backToFront(std::string &currentAlgorithm, int noOfRows, vector<vector<vec2>> activeTemplate, vector<vector<vec2>> activeDoorPos, vector<Passenger> &activePassengers);
	void seatBySeat(std::string &currentAlgorithm, int noOfRows, int noOfColumns, std::string aircraftName, vector<vector<vec2>> activeTemplate, vector<vector<vec2>> activeDoorPos, vector<Passenger> &activePassengers);
	void rowByRow(std::string &currentAlgorithm, int noOfRows, vector<vector<vec2>> activeTemplate, vector<vector<vec2>> activeDoorPos, vector<Passenger> &activePassengers);
	void randomSeat(std::string &currentAlgorithm, int noOfRows, int noOfColumns, std::string aircraftName, vector<vector<vec2>> activeTemplate, vector<vector<vec2>> activeDoorPos, vector<Passenger> &activePassengers);
};