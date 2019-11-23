#include "PhysicsEngine.h"

void PhysicsEngine::updatePositions(vector<Passenger> &activePassengers, vector<Passenger> &activeSeatedPassengers, float aislePosY) {
	//Updates positions and draws passengers
	for (size_t i = 0; i < activePassengers.size(); i++) {
		vec2 tempInitPos = activePassengers[i].getInitPos();
		float tempSpeed = activePassengers[i].getWalkingSpeed();
		float distanceCD = passengerRadius + tempSpeed;
		bool tempIsAisleAligned = activePassengers[i].getIsYAlignedWithAisle();
		bool tempIsWalkingRight = activePassengers[i].getIsWalkingRight();

		//If passenger is seated, move passenger to activeSeatedPassengers vector and move on to next passenger
		if (tempInitPos == activePassengers[i].getSeatPos()) {
			activeSeatedPassengers.push_back(activePassengers[i]);
			activePassengers.erase(activePassengers.begin() + i);
			continue;
		}


		//If aligned with the aisle, set to true
		if (tempInitPos.y == aislePosY) {
			activePassengers[i].setIsYAlignedWithAisle(true);
		}


		//Lines up passengers with the aisle
		if (!tempIsAisleAligned) {
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


		//Moves passengers to their seat row
		else if (!activePassengers[i].getIsRowFound()) {
			if ((tempInitPos.x + 2.0f) < activePassengers[i].getSeatPos().x) { //If to the left of the row, walk right
				vec2 newPos = tempInitPos + vec2(tempSpeed, 0.0f);
				for (size_t j = 0; j < activePassengers.size(); j++) {	//Collision detection

					if (abs(newPos.x - activePassengers[j].getInitPos().x) < distanceCD &&
						activePassengers[j].getIsYAlignedWithAisle() &&
						i != j) {
						if (tempIsWalkingRight != activePassengers[j].getIsWalkingRight() && 
							!activePassengers[j].getIsRowFound()) {
							newPos = tempInitPos + vec2(tempSpeed / 4, 0.0f);
							break;
						}
						else if (tempInitPos.x > activePassengers[j].getInitPos().x) {
							vec2 newPos = tempInitPos + vec2(tempSpeed, 0.0f);
						}
						else {
							newPos = tempInitPos;
						}
					}

				}
				activePassengers[i].setInitPos(newPos);
				activePassengers[i].setRotation(270.0f);
			}
			else if ((tempInitPos.x - 2.0f) > activePassengers[i].getSeatPos().x) {	//If to the right of the row, walk left
				vec2 newPos = tempInitPos + vec2(-tempSpeed, 0.0f);
				for (size_t j = 0; j < activePassengers.size(); j++) {	//Collision detection

					if (abs(newPos.x - activePassengers[j].getInitPos().x) < distanceCD &&
						activePassengers[j].getIsYAlignedWithAisle() &&
						i != j) {
						if (tempIsWalkingRight != activePassengers[j].getIsWalkingRight() && 
							!activePassengers[j].getIsRowFound()) {
							newPos = tempInitPos + vec2(-tempSpeed / 4, 0.0f);
							break;
						}
						else if (tempInitPos.x < activePassengers[j].getInitPos().x) {
							vec2 newPos = tempInitPos + vec2(-tempSpeed, 0.0f);
						}
						else {
							newPos = tempInitPos;
						}
					}

				}
				activePassengers[i].setInitPos(newPos);
				activePassengers[i].setRotation(90.0f);
			}
			else {
				activePassengers[i].setInitPos(vec2(activePassengers[i].getSeatPos().x, tempInitPos.y));
				activePassengers[i].setIsRowFound(true);
			}
		}
		else {	//When row found, walk up or down to get in the seat
			if (activePassengers[i].getBaggageTimerStart() < 0) {	//Sets timer when passenger starts to enter the seat row
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