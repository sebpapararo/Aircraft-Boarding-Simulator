#include "PhysicsEngine.h"

#include <chrono>

// Defining types
typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::milliseconds ms;
typedef std::chrono::duration<float> fsec;

auto lastDelta = Time::now();
auto currentDelta = Time::now();
bool firstLoop = true;


double PhysicsEngine::getSimSpeed() {
	return simSpeed;
}

void PhysicsEngine::setSimSpeed(double speed) {
	simSpeed = speed;
}


void PhysicsEngine::seatedPassengerPercentage(vector<Passenger> &activeSeatedPassengers, int noOfPassengers) {
	if (activeSeatedPassengers.size() == static_cast<int>(noOfPassengers * 0.2)) {
		std::cout << "20% of passengers are now seated!" << std::endl;
	}
	else if (activeSeatedPassengers.size() == static_cast<int>(noOfPassengers * 0.4)) {
		std::cout << "40% of passengers are now seated!" << std::endl;
	}
	else if (activeSeatedPassengers.size() == static_cast<int>(noOfPassengers * 0.6)) {
		std::cout << "60% of passengers are now seated!" << std::endl;
	}
	else if (activeSeatedPassengers.size() == static_cast<int>(noOfPassengers * 0.8)) {
		std::cout << "80% of passengers are now seated!" << std::endl;
	}
}


//void PhysicsEngine::updatePositions(vector<Passenger> &activePassengers, vector<Passenger> &activeSeatedPassengers, float aislePosY) {
void PhysicsEngine::updatePositions(vector<Passenger> &activePassengers, vector<Passenger> & activeSeatedPassengers, vector<float> aislePosY, std::chrono::steady_clock::time_point startTime, int noOfPassengers) {

	//on first iteration only initialise delta time
	if (firstLoop) {
		currentDelta = Time::now();
		firstLoop = false;
		return;
	}

	// calculating deltaTime
	lastDelta = currentDelta;
	currentDelta = Time::now();
	fsec ds = currentDelta - lastDelta;

	// Convert deltaTime into a double (should be somewhere around 0.02 ~)
	double doubleDt = ds.count();

	// If no time has passed since last iteration, dont move anything.
	if (ds.count() == 0) {
		std::cout << " NO TIME PASSED" << std::endl;
		return;
	}

	// For each passenger:
	for (size_t i = 0; i < activePassengers.size(); i++) {

		// Initialising passenger information
		vec2 tempInitPos = activePassengers[i].getInitPos();
		float distanceCD = passengerRadius + activePassengers[i].getCurrSpeed() * doubleDt;
		bool tempIsAisleAligned = activePassengers[i].getIsYAlignedWithAisle();
		bool tempIsWalkingRight = activePassengers[i].getIsWalkingRight();

		//If passenger is seated, move passenger to activeSeatedPassengers vector and move on to next passenger
		if (tempInitPos == activePassengers[i].getSeatPos()) {
			totalSeatedTime += std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - startTime).count();
			
			activeSeatedPassengers.push_back(activePassengers[i]);
			activePassengers.erase(activePassengers.begin() + i);
			seatedPassengerPercentage(activeSeatedPassengers, noOfPassengers);
			continue;
		}

		// ================== Movement Logic ==================

		//If aligned with the aisle, set to true
		if (tempInitPos.y == activePassengers[i].getAisleY()) {
			activePassengers[i].setIsYAlignedWithAisle(true);
		}

		//If passenger is not aligned with aisle
		if (!tempIsAisleAligned) {
			//If below aisle, walk up
			if (tempInitPos.y < activePassengers[i].getAisleY()) {
				vec2 newPos = tempInitPos + vec2(0.0f, activePassengers[i].accelerate() * doubleDt * simSpeed);

				//If collision detection does not overshoot the aisle position
				if (tempInitPos.y + distanceCD < activePassengers[i].getAisleY()) {

					// checking each passenger for collision detection:
					int apLength2 = activePassengers.size();
					for (size_t j = 0; j < apLength2; j++) {

						int xd = activePassengers[j].getInitPos().x - newPos.x;
						int yd = activePassengers[j].getInitPos().y - newPos.y;

						// if passenger is in the way, do not update position
						if (activePassengers[j].getInitPos().y > tempInitPos.y && sqrt(xd*xd + yd + yd) < distanceCD) {
							newPos -= vec2(0.0f, activePassengers[i].getCurrSpeed() * doubleDt * simSpeed);
							activePassengers[i].decelerate()* simSpeed;
							break;
						}
					}
				}
				//If passenger overshot the aisle, line up on the aisle
				if (tempInitPos.y + distanceCD >= activePassengers[i].getAisleY()) {
					activePassengers[i].setInitPos(vec2(tempInitPos.x, activePassengers[i].getAisleY()));
					activePassengers[i].setIsYAlignedWithAisle(true);
				}
				else {
					activePassengers[i].setInitPos(newPos);
				}
				activePassengers[i].setRotation(0.0f);
			}

			// else if the passenger is above its aisle, walk down
			else if (tempInitPos.y > activePassengers[i].getAisleY()) {

				vec2 newPos = tempInitPos + vec2(0.0f, -activePassengers[i].accelerate() * doubleDt * simSpeed);

				// checking each passenger for collision detection: 
				if (tempInitPos.y + distanceCD > activePassengers[i].getAisleY()) {

					int apLength3 = activePassengers.size();
					for (size_t j = 0; j < apLength3; j++) {
						int xd = newPos.x - activePassengers[j].getInitPos().x;
						int yd = newPos.y - activePassengers[j].getInitPos().y;
						// if passenger is in the way, dont move!
						if (activePassengers[j].getInitPos().y < tempInitPos.y && sqrt(xd*xd + yd + yd) < distanceCD) {
							newPos -= vec2(0.0f, -activePassengers[i].getCurrSpeed() * doubleDt * simSpeed);
							activePassengers[i].decelerate() * simSpeed;
							break;
						}
					}
				}
				// if the passenger has overshot the aisle, line him up on the aisle!
				if (tempInitPos.y + distanceCD <= activePassengers[i].getAisleY()) {
					activePassengers[i].setInitPos(vec2(tempInitPos.x, activePassengers[i].getAisleY()));
					activePassengers[i].setIsYAlignedWithAisle(true);
				}
				else {
					activePassengers[i].setInitPos(newPos);
				}
				activePassengers[i].setRotation(180.0f);
			}
		}
		//Moves passengers to their seat row
		else if (!activePassengers[i].getIsRowFound()) {
			
			if ((tempInitPos.x + 2.0f) < activePassengers[i].getSeatPos().x) { //If to the left of the row, walk right
				vec2 newPos = tempInitPos + vec2(activePassengers[i].accelerate() * doubleDt * simSpeed, 0.0f);

				int apLength4 = activePassengers.size();
				for (size_t j = 0; j < apLength4; j++) {	//Collision detection

					if (abs(newPos.x - activePassengers[j].getInitPos().x) < distanceCD && abs(newPos.y - activePassengers[j].getInitPos().y) < distanceCD &&
						activePassengers[j].getIsYAlignedWithAisle() &&
						i != j) {
						if (tempIsWalkingRight != activePassengers[j].getIsWalkingRight() && 
							!activePassengers[j].getIsRowFound()) {
							newPos = tempInitPos + vec2((activePassengers[i].getCurrSpeed() * doubleDt * simSpeed) / 4, 0.0f);
							break;
						}
						else if (tempInitPos.x > activePassengers[j].getInitPos().x) {
							vec2 newPos = tempInitPos + vec2(activePassengers[i].getCurrSpeed() * doubleDt * simSpeed, 0.0f);
						}
						else {
							newPos = tempInitPos;
						}
					}

				}
				// if the passenger has overshot the row, line him up on the row!
				if (newPos.x >= activePassengers[i].getSeatPos().x) {
					activePassengers[i].setInitPos(vec2(activePassengers[i].getSeatPos().x, newPos.y));
				}
				else {
					activePassengers[i].setInitPos(newPos);
				}
				activePassengers[i].setRotation(270.0f);
			}
			else if ((tempInitPos.x - 2.0f) > activePassengers[i].getSeatPos().x) {	//If to the right of the row, walk left
				vec2 newPos = tempInitPos + vec2(-activePassengers[i].accelerate() * doubleDt * simSpeed, 0.0f);

				int apLength5 = activePassengers.size();
				for (size_t j = 0; j < apLength5; j++) {	//Collision detection
					//If passenger does not collide with other passenger
					if (abs(newPos.x - activePassengers[j].getInitPos().x) < distanceCD && abs(newPos.y - activePassengers[j].getInitPos().y) < distanceCD &&
						activePassengers[j].getIsYAlignedWithAisle() &&
						i != j) {
						//If passsenger is not walking in the same direction as other passenger
						if (tempIsWalkingRight != activePassengers[j].getIsWalkingRight() && 
							!activePassengers[j].getIsRowFound()) {
							newPos = tempInitPos + vec2((-activePassengers[i].getCurrSpeed() * doubleDt * simSpeed) / 4, 0.0f);
							break;
						}
						//Else if passenger is to the left of other passenger
						else if (tempInitPos.x < activePassengers[j].getInitPos().x) {
							vec2 newPos = tempInitPos + vec2(-activePassengers[i].getCurrSpeed() * doubleDt * simSpeed, 0.0f);
						}
						//Else do not update position
						else {
							newPos = tempInitPos;
						}
					}

				}
				// if passenger overshot the row, line up on the row
				if (newPos.x <= activePassengers[i].getSeatPos().x) {
					activePassengers[i].setInitPos(vec2(activePassengers[i].getSeatPos().x, newPos.y));
				}
				else {
					activePassengers[i].setInitPos(newPos);
				}
				activePassengers[i].setRotation(90.0f);
			}
			// if passenger is neither to the left or right of the row, row is found and set rowFound to true
			else {
				activePassengers[i].setInitPos(vec2(activePassengers[i].getSeatPos().x, tempInitPos.y));
				activePassengers[i].setIsRowFound(true);
			}
		}
		//When row found, walk up or down to get in the seat
		else {
			if (activePassengers[i].getBaggageTimerStart() <= 0) {	//Sets timer when passenger starts to enter the seat row
				activePassengers[i].setBaggageTimerStart(glutGet(GLUT_ELAPSED_TIME));
			}
			else if ((glutGet(GLUT_ELAPSED_TIME) - activePassengers[i].getBaggageTimerStart()) < 1000 / simSpeed) {	//If passenger waits less than one second
				//Do nothing
			}

			// else if the passenger is below its seat, walk up
			else if (tempInitPos.y < activePassengers[i].getSeatPos().y) {
				vec2 tempPos = tempInitPos + vec2(0.0f, activePassengers[i].accelerate() * doubleDt * simSpeed);

				// if passenger overshot the seat, line up on the seat
				if (tempPos.y >= activePassengers[i].getSeatPos().y) {
					activePassengers[i].setInitPos(vec2(tempPos.x, activePassengers[i].getSeatPos().y));
				}
				else {
					activePassengers[i].setInitPos(tempInitPos + vec2(0.0f, activePassengers[i].getCurrSpeed() * doubleDt * simSpeed));
				}
				activePassengers[i].setRotation(0.0f);
			}
			// else if the passenger is above its seat, walk down 
			else if (tempInitPos.y > activePassengers[i].getSeatPos().y) {
				vec2 tempPos = tempInitPos + vec2(0.0f, -activePassengers[i].accelerate() * doubleDt * simSpeed);

				// if passenger overshot the seat, line up on the seat
				if (tempPos.y <= activePassengers[i].getSeatPos().y) {
					activePassengers[i].setInitPos(vec2(tempPos.x, activePassengers[i].getSeatPos().y));
				}
				else {
					activePassengers[i].setInitPos(tempInitPos + vec2(0.0f, -activePassengers[i].getCurrSpeed() * doubleDt * simSpeed));
				}
				activePassengers[i].setRotation(180.0f);
			}
		}
	}

	//Calculates average time for a passenger to be seated
	if (activePassengers.empty()) {
		averageSeatedTime = totalSeatedTime / activeSeatedPassengers.size();
	}
}

double PhysicsEngine::getAverageSeatedTime() {
	return averageSeatedTime;
}

void PhysicsEngine::resetDelta() {
	lastDelta = Time::now();
	currentDelta = Time::now();
}