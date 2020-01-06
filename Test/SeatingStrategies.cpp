#include "SeatingStrategies.h"

void SeatingStrategies::backToFront(std::string &currentAlgorithm, int noOfRows, vector<vector<vec2>> activeTemplate, vector<vector<vec2>> activeDoorPos, int actveDoorsSelect, vector<Passenger> &activePassengers, vector<float> aislePosY) {
	currentAlgorithm = "Back-To-Front";
	int count1 = 0;
	int count2 = 0;

	for (int i = noOfRows-1; i > -1; i--) {
		int atSize = activeTemplate[i].size();
		for (size_t j = 0; j < atSize; j++) {
			Passenger *p;
			
			if (actveDoorsSelect == 1) {
				p = new Passenger(activeTemplate[i][j], activeDoorPos[1][1] + vec2(0.0f, (-10.0f * count1)), false);	//Passengers enter through rear-left door
				count1++;
			}
			else if (actveDoorsSelect == 2) {
				p = new Passenger(activeTemplate[i][j], activeDoorPos[0][1] + vec2(0.0f, (-10.0f * count2)), true);		//Passengers enter through front-left door
				count2++;
			}
			else { // If 3, then initialize for front and rear door
				if (i < noOfRows/2) {
					p = new Passenger(activeTemplate[i][j], activeDoorPos[0][1] + vec2(0.0f, (-10.0f * count1)), false);	//Passengers enter through front-left door
					count1++;
				}
				else {
					p = new Passenger(activeTemplate[i][j], activeDoorPos[1][1] + vec2(0.0f, (-10.0f * count2)), true);		//Passengers enter through rear-left door
					count2++;
				}
			}

			if (j > (activeTemplate[i].size() / 2) - 1 && aislePosY.size() > 1) {
				p->setAisleY(aislePosY[1]);
			}
			else {
				p->setAisleY(aislePosY[0]);
			}
			activePassengers.push_back(*p);
		}
	}
}

void SeatingStrategies::insideOut(std::string &currentAlgorithm, int noOfRows, vector<vector<vec2>> activeTemplate, vector<vector<vec2>> activeDoorPos, int actveDoorsSelect, vector<Passenger> &activePassengers, vector<float> aislePosY) {
	currentAlgorithm = "Inside-Out";
	int count1 = 0;
	int count2 = 0;

	for (int i = (noOfRows / 2) - 1; i > -1; i--) {
		int atSize = activeTemplate[i].size();
		for (size_t j = 0; j < atSize; j++) {
			Passenger *p;

			if (actveDoorsSelect == 1) {
				p = new Passenger(activeTemplate[i][j], activeDoorPos[1][1] + vec2(0.0f, (-10.0f * count1)), false);	//Passengers enter through rear-left door
				count1++;
			}
			else if (actveDoorsSelect == 2) {
				p = new Passenger(activeTemplate[i][j], activeDoorPos[0][1] + vec2(0.0f, (-10.0f * count2)), true);		//Passengers enter through front-left door
				count2++;
			}
			else { // If 3, then initialize for front and rear door
				p = new Passenger(activeTemplate[i][j], activeDoorPos[0][1] + vec2(0.0f, (-10.0f * count1)), false);	//Passengers enter through front-left door
				count1++;
			}

			if (j > (activeTemplate[i].size() / 2) - 1 && aislePosY.size() > 1) {
				p->setAisleY(aislePosY[1]);
			}
			else {
				p->setAisleY(aislePosY[0]);
			}
			activePassengers.push_back(*p);
		}
	}

	for (int i = noOfRows / 2; i < noOfRows; i++) {
		int atSize = activeTemplate[i].size();
		for (size_t j = 0; j < atSize; j++) {
			Passenger *p;

			if (actveDoorsSelect == 1) {
				p = new Passenger(activeTemplate[i][j], activeDoorPos[1][1] + vec2(0.0f, (-10.0f * count1)), false);	//Passengers enter through rear-left door
				count1++;
			}
			else if (actveDoorsSelect == 2) {
				p = new Passenger(activeTemplate[i][j], activeDoorPos[0][1] + vec2(0.0f, (-10.0f * count2)), true);		//Passengers enter through front-left door
				count2++;
			}
			else { // If 3, then initialize for front and rear door
				p = new Passenger(activeTemplate[i][j], activeDoorPos[1][1] + vec2(0.0f, (-10.0f * count2)), true);		//Passengers enter through rear-left door
				count2++;
			}

			if (j > (activeTemplate[i].size() / 2) - 1 && aislePosY.size() > 1) {
				p->setAisleY(aislePosY[1]);
			}
			else {
				p->setAisleY(aislePosY[0]);
			}
			activePassengers.push_back(*p);
		}
	}
}

void SeatingStrategies::outsideIn(std::string &currentAlgorithm, int noOfRows, vector<vector<vec2>> activeTemplate, vector<vector<vec2>> activeDoorPos, int actveDoorsSelect, vector<Passenger> &activePassengers, vector<float> aislePosY) {
	currentAlgorithm = "Outside-In";
	int count1 = 0;
	int count2 = 0;

	for (int i = 0; i < (noOfRows/2); i++) {
		int atSize = activeTemplate[i].size();
		for (size_t j = 0; j < atSize; j++) {
			Passenger *p;

			if (actveDoorsSelect == 1) {
				p = new Passenger(activeTemplate[i][j], activeDoorPos[1][1] + vec2(0.0f, (-10.0f * count1)), false);	//Passengers enter through rear-left door
				count1++;
			}
			else if (actveDoorsSelect == 2) {
				p = new Passenger(activeTemplate[i][j], activeDoorPos[0][1] + vec2(0.0f, (-10.0f * count2)), true);		//Passengers enter through front-left door
				count2++;
			}
			else { // If 3, then initialize for front and rear door
				p = new Passenger(activeTemplate[i][j], activeDoorPos[0][1] + vec2(0.0f, (-10.0f * count1)), false);	//Passengers enter through front-left door
				count1++;
			}

			if (j > (activeTemplate[i].size() / 2) - 1 && aislePosY.size() > 1) {
				p->setAisleY(aislePosY[1]);
			}
			else {
				p->setAisleY(aislePosY[0]);
			}
			activePassengers.push_back(*p);
		}
	}

	for (int i = noOfRows-1; i > noOfRows/2-1; i--) {
		int atSize = activeTemplate[i].size();
		for (size_t j = 0; j < atSize; j++) {
			Passenger *p;

			if (actveDoorsSelect == 1) {
				p = new Passenger(activeTemplate[i][j], activeDoorPos[1][1] + vec2(0.0f, (-10.0f * count1)), false);	//Passengers enter through rear-left door
				count1++;
			}
			else if (actveDoorsSelect == 2) {
				p = new Passenger(activeTemplate[i][j], activeDoorPos[0][1] + vec2(0.0f, (-10.0f * count2)), true);		//Passengers enter through front-left door
				count2++;
			}
			else { // If 3, then initialize for front and rear door
				p = new Passenger(activeTemplate[i][j], activeDoorPos[1][1] + vec2(0.0f, (-10.0f * count2)), true);		//Passengers enter through rear-left door
				count2++;
			}

			if (j > (activeTemplate[i].size() / 2) - 1 && aislePosY.size() > 1) {
				p->setAisleY(aislePosY[1]);
			}
			else {
				p->setAisleY(aislePosY[0]);
			}
			activePassengers.push_back(*p);
		}
	}
}

void SeatingStrategies::seatBySeat(std::string &currentAlgorithm, int noOfRows, int noOfColumns, std::string aircraftName, vector<vector<vec2>> activeTemplate, vector<vector<vec2>> activeDoorPos, int actveDoorsSelect, vector<Passenger> &activePassengers, vector<float> aislePosY) {
	currentAlgorithm = "Seat-By-Seat";
	int count1 = 0;
	int count2 = 0;
	for (int i = 0; i < noOfColumns; i++) {
		for (int j = 0; j < noOfRows; j++) {

			if (activeTemplate[j].size()-1 < i) {
				continue;
			}

			Passenger *p;

			if (actveDoorsSelect == 1) {
				p = new Passenger(activeTemplate[j][i], activeDoorPos[1][1] + vec2(0.0f, (-10.0f * count1)), false);	//Passengers enter through rear-left door
				count1++;
			}
			else if (actveDoorsSelect == 2) {
				p = new Passenger(activeTemplate[j][i], activeDoorPos[0][1] + vec2(0.0f, (-10.0f * count2)), true);		//Passengers enter through front-left door
				count2++;
			}
			else { // If 3, then initialize for front and rear door
				if (j < noOfRows / 2) {
					p = new Passenger(activeTemplate[j][i], activeDoorPos[0][1] + vec2(0.0f, (-10.0f * count1)), false);	//Passengers enter through front-left door
					count1++;
				}
				else {
					p = new Passenger(activeTemplate[j][i], activeDoorPos[1][1] + vec2(0.0f, (-10.0f * count2)), true);		//Passengers enter through rear-left door
					count2++;
				}
			}
			
			if (j > (activeTemplate[i].size() / 2) - 1 && aislePosY.size() > 1) {
				p->setAisleY(aislePosY[1]);
			}
			else {
				p->setAisleY(aislePosY[0]);
			}
			activePassengers.push_back(*p);
		}
	}
}

void SeatingStrategies::rowByRow(std::string &currentAlgorithm, int noOfRows, vector<vector<vec2>> activeTemplate, vector<vector<vec2>> activeDoorPos, int actveDoorsSelect, vector<Passenger> &activePassengers, vector<float> aislePosY) {
	currentAlgorithm = "Row-By-Row";
	int count1 = 0;
	int count2 = 0;
	for (int i = 0; i < noOfRows; i++) {
		int atSize = activeTemplate[i].size();
		for (size_t j = 0; j < atSize; j++) {
			Passenger *p;
			
			if (actveDoorsSelect == 1) {
				p = new Passenger(activeTemplate[i][j], activeDoorPos[1][1] + vec2(0.0f, (-10.0f * count1)), false);	//Passengers enter through rear-left door
				count1++;
			}
			else if (actveDoorsSelect == 2) {
				p = new Passenger(activeTemplate[i][j], activeDoorPos[0][1] + vec2(0.0f, (-10.0f * count2)), true);		//Passengers enter through front-left door
				count2++;
			}
			else { // If 3, then initialize for front and rear door
				if (i < noOfRows / 2) {
					p = new Passenger(activeTemplate[i][j], activeDoorPos[0][1] + vec2(0.0f, (-10.0f * count1)), false);	//Passengers enter through front-left door
					count1++;
				}
				else {
					p = new Passenger(activeTemplate[i][j], activeDoorPos[1][1] + vec2(0.0f, (-10.0f * count2)), true);		//Passengers enter through rear-left door
					count2++;
				}
			}

			if (j > (activeTemplate[i].size() / 2) - 1 && aislePosY.size() > 1) {
				p->setAisleY(aislePosY[1]);
			}
			else {
				p->setAisleY(aislePosY[0]);
			}
			activePassengers.push_back(*p);
		}
	}
}

void SeatingStrategies::randomSeat(std::string &currentAlgorithm, int noOfRows, int noOfColumns, std::string aircraftName, vector<vector<vec2>> activeTemplate, vector<vector<vec2>> activeDoorPos, int actveDoorsSelect, vector<Passenger> &activePassengers, vector<float> aislePosY) {
	currentAlgorithm = "Random";

	int count1 = 0;
	int count2 = 0;
	vector<int> numbers;

	srand(time(0));
	std::random_shuffle(activeTemplate.begin(), activeTemplate.end());

	for (int i = 0; i < noOfRows; i++) {
		int atSize = activeTemplate[i].size();
		for (int j = 0; j < atSize; j++) {
			Passenger *p;

			if (actveDoorsSelect == 1) {
				p = new Passenger(activeTemplate[i][j], activeDoorPos[1][1] + vec2(0.0f, (-10.0f * count1)), false);	//Passengers enter through rear-left door
				count1++;
			}
			else if (actveDoorsSelect == 2) {
				p = new Passenger(activeTemplate[i][j], activeDoorPos[0][1] + vec2(0.0f, (-10.0f * count2)), true);		//Passengers enter through front-left door
				count2++;
			}
			else { // If 3, then initialize for front and rear door
				if (rand() % 2 == 0) {
					p = new Passenger(activeTemplate[i][j], activeDoorPos[1][1] + vec2(0.0f, (-10.0f * count1)), false);	//Passengers enter through rear-left door
					count1++;
				}
				else {
					p = new Passenger(activeTemplate[i][j], activeDoorPos[0][1] + vec2(0.0f, (-10.0f * count2)), true);		//Passengers enter through front-left door
					count2++;
				}
			}

			if (j > (activeTemplate[i].size() / 2) - 1 && aislePosY.size() > 1) {
				p->setAisleY(aislePosY[1]);
			}
			else {
				p->setAisleY(aislePosY[0]);
			}
			activePassengers.push_back(*p);
		}
	}
}