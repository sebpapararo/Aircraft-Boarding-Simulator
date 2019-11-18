#include "SeatingStrategies.h"
#include <algorithm>

// TODO: Needs to be completely rewritten to include zones otherwise it is just the same as row by row but backwards
void SeatingStrategies::backToFront(std::string &currentAlgorithm, int noOfRows, vector<vector<vec2>> activeTemplate, vector<vector<vec2>> activeDoorPos, vector<Passenger> &activePassengers) {
	currentAlgorithm = "Back-To-Front";
	int count = 0;
	for (int i = 0; i < noOfRows; i++) {
		for (size_t j = 0; j < activeTemplate[i].size(); j += 2) {
			//Passenger *p = new Passenger(activeTemplate[i][j], activeDoorPos[1][0] + vec2(0.0f, (10.0f * count)));	//Sets seat and starting positions
			//Passenger *p = new Passenger(activeTemplate[i][j], activeDoorPos[1][1] + vec2(0.0f, (-10.0f * count)));	//Sets seat and starting positions
			//activePassengers.push_back(*p);

			Passenger *p = new Passenger(activeTemplate[i][j], activeDoorPos[0][1] + vec2(0.0f, (-10.0f * count)));
			Passenger *p2 = new Passenger(activeTemplate[i][j], activeDoorPos[1][1] + vec2(0.0f, (-10.0f * count)));
			activePassengers.push_back(*p);
			activePassengers.push_back(*p2);
			count++;
		}
	}
}

// TODO: maybe change it so it treats the first row as part of the last 3 columns instead of the first 3
void SeatingStrategies::seatBySeat(std::string &currentAlgorithm, int noOfRows, int noOfColumns, std::string aircraftName, vector<vector<vec2>> activeTemplate, vector<vector<vec2>> activeDoorPos, vector<Passenger> &activePassengers) {
	currentAlgorithm = "Seat-By-Seat";
	int count = 0;
	for (int i = 0; i < noOfColumns; i++) {
		for (int j = 0; j < noOfRows; j++) {
			// Only do this for the Boeing 737. It ensures that passengers are not created for the 3 missing seats in the front row
			if (aircraftName == "Boeing 737-800" && j == 0 && (i == 3 || i == 4 || i == 5)) {
				continue;
			}
			Passenger* p = new Passenger(activeTemplate[j][i], activeDoorPos[1][1] + vec2(0.0f, (-20.0f * count)));	//Sets seat and starting positions
			activePassengers.push_back(*p);
			count++;
		}
	}
}

void SeatingStrategies::rowByRow(std::string &currentAlgorithm, int noOfRows, vector<vector<vec2>> activeTemplate, vector<vector<vec2>> activeDoorPos, vector<Passenger> &activePassengers) {
	currentAlgorithm = "Row-By-Row";
	int count = 0;
	for (int i = 0; i < noOfRows; i++) {
		for (size_t j = 0; j < activeTemplate[i].size(); j++) {
			Passenger* p = new Passenger(activeTemplate[i][j], activeDoorPos[1][1] + vec2(0.0f, (-20.0f * count)));	//Sets seat and starting positions
			activePassengers.push_back(*p);
			count++;
		}
	}
}

void SeatingStrategies::randomSeat(std::string &currentAlgorithm, int noOfRows, int noOfColumns, std::string aircraftName, vector<vector<vec2>> activeTemplate, vector<vector<vec2>> activeDoorPos, vector<Passenger> &activePassengers) {
	currentAlgorithm = "Random";
	int count = 0;
	vector<int> numbers;
	int noOfSeats = noOfRows * noOfColumns;

	// filling an array with seat numbers
	for (int i = 0; i < noOfSeats; i++) {
		numbers.push_back(i);
	}

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	shuffle(numbers.begin(), numbers.end(), std::default_random_engine(seed));

	for (int i = 0; i < noOfSeats; i++) {
		// Only do this for the Boeing 737. It ensures that passengers are not created for the 3 missing seats in the front row
		if (aircraftName == "Boeing 737-800" && numbers[i] / noOfColumns == 0 && (numbers[i] % noOfColumns == 3 || numbers[i] % noOfColumns == 4 || numbers[i] % noOfColumns == 5)) {
			continue;
		}
		Passenger *p = new Passenger(activeTemplate[numbers[i] / noOfColumns][numbers[i] % noOfColumns], activeDoorPos[1][1] + vec2(0.0f, (-20.0f * count)));	//Sets seat and starting positions
		activePassengers.push_back(*p);
		count++;
	}
}