#pragma once
#include "Passenger.h"

#include <chrono>
#include <random>
#include <vector>
#include <algorithm>

using std::vector;

class SeatingStrategies {
public:
	void backToFront(std::string &currentAlgorithm, int noOfRows, vector<vector<vec2>> activeTemplate, vector<vector<vec2>> activeDoorPos, int actveDoorsSelect, vector<Passenger> &activePassengers, vector<float> aislePosY);
	void insideOut(std::string &currentAlgorithm, int noOfRows, vector<vector<vec2>> activeTemplate, vector<vector<vec2>> activeDoorPos, int actveDoorsSelect, vector<Passenger> &activePassengers, vector<float> aislePosY);
	void outsideIn(std::string &currentAlgorithm, int noOfRows, vector<vector<vec2>> activeTemplate, vector<vector<vec2>> activeDoorPos, int actveDoorsSelect, vector<Passenger> &activePassengers, vector<float> aislePosY);
	void seatBySeat(std::string &currentAlgorithm, int noOfRows, int noOfColumns, std::string aircraftName, vector<vector<vec2>> activeTemplate, vector<vector<vec2>> activeDoorPos, int actveDoorsSelect, vector<Passenger> &activePassengers, vector<float> aislePosY);
	void rowByRow(std::string &currentAlgorithm, int noOfRows, vector<vector<vec2>> activeTemplate, vector<vector<vec2>> activeDoorPos, int actveDoorsSelect, vector<Passenger> &activePassengers, vector<float> aislePosY);
	void randomSeat(std::string &currentAlgorithm, int noOfRows, int noOfColumns, std::string aircraftName, vector<vector<vec2>> activeTemplate, vector<vector<vec2>> activeDoorPos, int actveDoorsSelect, vector<Passenger> &activePassengers, vector<float> aislePosY);
};