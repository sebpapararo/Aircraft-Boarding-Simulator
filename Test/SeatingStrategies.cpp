#include "SeatingStrategies.h"

// TODO: Needs to be completely rewritten to include zones otherwise it is just the same as row by row but backwards
void SeatingStrategies::backToFront(std::string &currentAlgorithm, int noOfRows, vector<vector<vec2>> activeTemplate, vector<vector<vec2>> activeDoorPos, int actveDoorsSelect, vector<Passenger> &activePassengers, vector<float> aislePosY) {
	currentAlgorithm = "Back-To-Front";
	//int count = 0;
	int count1 = 0;
	int count2 = 0;

	for (int i = 0; i < noOfRows; i++) {
		for (size_t j = 0; j < activeTemplate[i].size(); j++) {
			Passenger *p;
			
			//p = new Passenger(activeTemplate[i][j], activeDoorPos[1][1] + vec2(0.0f, (-10.0f * count)), false);	//Sets seat and starting positions
			
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
			//count++;
		}
	}
}

void SeatingStrategies::insideOut(std::string &currentAlgorithm, int noOfRows, vector<vector<vec2>> activeTemplate, vector<vector<vec2>> activeDoorPos, int actveDoorsSelect, vector<Passenger> &activePassengers, vector<float> aislePosY) {
	currentAlgorithm = "Inside-Out";
	int count1 = 0;
	int count2 = 0;

	for (int i = (noOfRows / 2) - 1; i > -1; i--) {
		for (size_t j = 0; j < activeTemplate[i].size(); j++) {
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
		for (size_t j = 0; j < activeTemplate[i].size(); j++) {
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
		for (size_t j = 0; j < activeTemplate[i].size(); j++) {
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
		for (size_t j = 0; j < activeTemplate[i].size(); j++) {
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

// TODO: maybe change it so it treats the first row as part of the last 3 columns instead of the first 3
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
			//p = new Passenger(activeTemplate[j][i], activeDoorPos[1][1] + vec2(0.0f, (-10.0f * count)), false);	//Sets seat and starting positions

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
			//count++;
		}
	}
}

void SeatingStrategies::rowByRow(std::string &currentAlgorithm, int noOfRows, vector<vector<vec2>> activeTemplate, vector<vector<vec2>> activeDoorPos, int actveDoorsSelect, vector<Passenger> &activePassengers, vector<float> aislePosY) {
	currentAlgorithm = "Row-By-Row";
	int count1 = 0;
	int count2 = 0;
	for (int i = 0; i < noOfRows; i++) {
		for (size_t j = 0; j < activeTemplate[i].size(); j++) {
			Passenger *p;
			//p = new Passenger(activeTemplate[i][j], activeDoorPos[1][1] + vec2(0.0f, (-10.0f * count)), false);	//Sets seat and starting positions
			
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
			//count++;
		}
	}
}

void SeatingStrategies::randomSeat(std::string &currentAlgorithm, int noOfRows, int noOfColumns, std::string aircraftName, vector<vector<vec2>> activeTemplate, vector<vector<vec2>> activeDoorPos, int actveDoorsSelect, vector<Passenger> &activePassengers, vector<float> aislePosY) {
	currentAlgorithm = "Random";

	vector<vec2> currDoor;
	if (actveDoorsSelect == 1) {
		currDoor.push_back(activeDoorPos[1][1]);
	}
	else if (actveDoorsSelect == 2) {
		currDoor.push_back(activeDoorPos[0][1]);
	}
	else {
		currDoor = { activeDoorPos[0][1], activeDoorPos[1][1] };
	}

	int count1 = 0;
	int count2 = 0;
	vector<int> numbers;

	srand(time(0));
	std::random_shuffle(activeTemplate.begin(), activeTemplate.end());

	for (int i = 0; i < noOfRows; i++) {
		for (int j = 0; j < activeTemplate[i].size(); j++) {
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