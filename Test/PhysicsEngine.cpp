#include "PhysicsEngine.h"

#include <chrono>

// Defining types
typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::milliseconds ms;
typedef std::chrono::duration<float> fsec;

float ticksPerSecond = 100;

auto lastDelta = Time::now();
auto currentDelta = Time::now();
bool firstLoop = true;

void PhysicsEngine::updatePositions(vector<Passenger> &activePassengers, vector<Passenger> &activeSeatedPassengers, float aislePosY) {

	if (firstLoop) {
		currentDelta = Time::now();
		firstLoop = false;
		// on first iteration only initialise delta time
		return;
	}

	// calculating deltaTime
	lastDelta = currentDelta;
	currentDelta = Time::now();
	fsec ds = currentDelta - lastDelta;

	// conerting deltaTime into a float (should be somewhere around 0.02 ~)
	float floatDt = ds.count();

	// If no time has passed since last iteration, dont move anything.
	if (ds.count() == 0) {
		std::cout << " NO TIME PASSED" << std::endl;
		return;
	}

	//Updates positions and draws passengers
	// For each passenger: 
	for (size_t i = 0; i < activePassengers.size(); i++) {
		// Initialising passanger information
		vec2 tempInitPos = activePassengers[i].getInitPos();
		float tempSpeed = (activePassengers[i].getWalkingSpeed() * floatDt);
		float distanceCD = passengerRadius + tempSpeed;
		bool tempIsAligned = activePassengers[i].getIsAligned();

		//If passenger is seated, move passenger to activeSeatedPassengers vector and move on to next passenger
		if (tempInitPos == activePassengers[i].getSeatPos()) {
			activeSeatedPassengers.push_back(activePassengers[i]);
			activePassengers.erase(activePassengers.begin() + i);
			continue;
		}

		//If passenger is aligned with the aisle, set to true
		if (tempInitPos.y == aislePosY) {
			activePassengers[i].setIsAligned(true);
		}

		//Logic to line up passengers with the aisle
		if (!activePassengers[i].getIsAligned()) {
			if (tempInitPos.y < aislePosY) {											//If below aisle, walk up
				vec2 newPos = tempInitPos + vec2(0.0f, tempSpeed);
				if (tempInitPos.y + distanceCD < aislePosY) {
					for (size_t j = 0; j < activePassengers.size(); j++) {						//Collision detection
						int xd = activePassengers[j].getInitPos().x - newPos.x;
						int yd = activePassengers[j].getInitPos().y - newPos.y;
						if (activePassengers[j].getInitPos().y > tempInitPos.y && sqrt(xd*xd + yd + yd) < distanceCD) {
							newPos -= vec2(0.0f, tempSpeed);
							break;
						}
					}
				}
				activePassengers[i].setInitPos(newPos);
				activePassengers[i].setRotation(0.0f);
			}
			else if (tempInitPos.y > aislePosY) {										//If above aisle, walk down
				vec2 newPos = tempInitPos + vec2(0.0f, -tempSpeed);
				if (tempInitPos.y + distanceCD > aislePosY) {
					for (size_t j = 0; j < activePassengers.size(); j++) {						//Collision detection
						int xd = newPos.x - activePassengers[j].getInitPos().x;
						int yd = newPos.y - activePassengers[j].getInitPos().y;
						if (activePassengers[j].getInitPos().y < tempInitPos.y && sqrt(xd*xd + yd + yd) < distanceCD) {
							newPos -= vec2(0.0f, -tempSpeed);
							break;
						}
					}
				}
				activePassengers[i].setInitPos(newPos);
				activePassengers[i].setRotation(180.0f);
			}
		}

		//Logic to move passengers in their seats
		else {
			if (tempInitPos.x < activePassengers[i].getSeatPos().x) { //If to the left of the row, walk right
				vec2 newPos = tempInitPos + vec2(tempSpeed, 0.0f);
				for (size_t j = 0; j < activePassengers.size(); j++) {	//Collision detection
					if (abs(newPos.x - activePassengers[j].getInitPos().x) < distanceCD && abs(newPos.y - activePassengers[j].getInitPos().y) < distanceCD && activePassengers[j].getInitPos().x != tempInitPos.x) {
						newPos -= vec2(tempSpeed, 0.0f);
						break;
					}
				}
				activePassengers[i].setInitPos(newPos);
				activePassengers[i].setRotation(270.0f);
			}
			else if (tempInitPos.x > activePassengers[i].getSeatPos().x) {	//If to the right of the row, walk left
				vec2 newPos = tempInitPos + vec2(-tempSpeed, 0.0f);
				for (size_t j = 0; j < activePassengers.size(); j++) {	//Collision detection
					if (abs(newPos.x - activePassengers[j].getInitPos().x) < distanceCD && abs(newPos.y - activePassengers[j].getInitPos().y) < distanceCD && activePassengers[j].getInitPos().x != tempInitPos.x) {
						newPos -= vec2(-tempSpeed, 0.0f);
						break;
					}
				}
				activePassengers[i].setInitPos(newPos);
				activePassengers[i].setRotation(90.0f);
			}
			else {	//When row found, walk up or down to get in the seat
				if (activePassengers[i].getBaggageTimerStart() < 0) {	//Sets timer when passenger starts to enter the seat row
					activePassengers[i].setIsRowFound(true);
					activePassengers[i].setBaggageTimerStart(glutGet(GLUT_ELAPSED_TIME));
				}
				else if ((glutGet(GLUT_ELAPSED_TIME) - activePassengers[i].getBaggageTimerStart()) < 1000) {	//If passenger waits less than one second
					//Do nothing
				}
				else if (tempInitPos.y < activePassengers[i].getSeatPos().y) {
					activePassengers[i].setInitPos(tempInitPos + vec2(0.0f, tempSpeed));
					activePassengers[i].setRotation(0.0f);
				}
				else if (tempInitPos.y > activePassengers[i].getSeatPos().y) {
					activePassengers[i].setInitPos(tempInitPos + vec2(0.0f, -tempSpeed));
					activePassengers[i].setRotation(180.0f);
				}
			}
		}
	}
}