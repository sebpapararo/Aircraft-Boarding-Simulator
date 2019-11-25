#include "PhysicsEngine.h"

#include <chrono>

// Defining types
typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::milliseconds ms;
typedef std::chrono::duration<float> fsec;

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

	// conerting deltaTime into a double (should be somewhere around 0.02 ~)
	double doubleDt = ds.count();

	// If no time has passed since last iteration, dont move anything.
	if (ds.count() == 0) {
		std::cout << " NO TIME PASSED" << std::endl;
		return;
	}


	// For each passenger: 
	for (size_t i = 0; i < activePassengers.size(); i++) {

		// Initialising passanger information
		vec2 tempInitPos = activePassengers[i].getInitPos();
		float tempSpeed = (activePassengers[i].getWalkingSpeed() * doubleDt);
		float distanceCD = passengerRadius + tempSpeed;
		bool tempIsAisleAligned = activePassengers[i].getIsYAlignedWithAisle();
		bool tempIsWalkingRight = activePassengers[i].getIsWalkingRight();

		//If passenger is seated, move passenger to activeSeatedPassengers vector and move on to next passenger
		if (tempInitPos == activePassengers[i].getSeatPos()) {
			activeSeatedPassengers.push_back(activePassengers[i]);
			activePassengers.erase(activePassengers.begin() + i);
			continue;
		}

		// ================== Movement Logic ==================

		//If aligned with the aisle, set to true
		if (tempInitPos.y == aislePosY) {
			activePassengers[i].setIsYAlignedWithAisle(true);
		}

		// TODO: collision detection needs some work, because there position is calculated before checks for overshooting
		//		 happen, collisions may be detected even when they will not occur!

		//Lines up passengers with the aisle
		if (!tempIsAisleAligned) {
			if (tempInitPos.y < aislePosY) {											//If below aisle, walk up
				vec2 newPos = tempInitPos + vec2(0.0f, tempSpeed);

				if (tempInitPos.y + distanceCD < aislePosY) {

					// checking each passenger for collision detection: 
					for (size_t j = 0; j < activePassengers.size(); j++) {			

						int xd = activePassengers[j].getInitPos().x - newPos.x;
						int yd = activePassengers[j].getInitPos().y - newPos.y;

						// if passenger is in the way, dont move!
						if (activePassengers[j].getInitPos().y > tempInitPos.y && sqrt(xd*xd + yd + yd) < distanceCD) {
							newPos -= vec2(0.0f, tempSpeed);
							break;
						}
					}
				}
				// if the passenger has overshot the aisle, line him up on the aisle! TODO: move passengers who have overshot the aisle, into the aisle the distance they overshot!
				if (tempInitPos.y + distanceCD >= aislePosY) {
					activePassengers[i].setInitPos(vec2(tempInitPos.x, aislePosY));
					activePassengers[i].setIsYAlignedWithAisle(true);
				}
				else {
					activePassengers[i].setInitPos(newPos);
				}
				activePassengers[i].setRotation(0.0f);
			}

			// else if the passenger is above its aisle, walk down
			else if (tempInitPos.y > aislePosY) {		

				vec2 newPos = tempInitPos + vec2(0.0f, -tempSpeed);

				// checking each passenger for collision detection: 
				if (tempInitPos.y + distanceCD > aislePosY) {

					for (size_t j = 0; j < activePassengers.size(); j++) {
						int xd = newPos.x - activePassengers[j].getInitPos().x;
						int yd = newPos.y - activePassengers[j].getInitPos().y;
						// if passenger is in the way, dont move!
						if (activePassengers[j].getInitPos().y < tempInitPos.y && sqrt(xd*xd + yd + yd) < distanceCD) {
							newPos -= vec2(0.0f, -tempSpeed);
							break;
						}
					}
				}
				// if the passenger has overshot the aisle, line him up on the aisle!
				if (tempInitPos.y + distanceCD <= aislePosY) {
					activePassengers[i].setInitPos(vec2(tempInitPos.x, aislePosY));
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
				// if the passenger has overshot the row, line him up on the row!
				if (newPos.x >= activePassengers[i].getSeatPos().x) {
					activePassengers[i].setInitPos(vec2(activePassengers[i].getSeatPos().x,newPos.y));
				}
				else {
					activePassengers[i].setInitPos(newPos);
				}
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
				// if the passenger has overshot the row, line him up on the row!
				if (newPos.x <= activePassengers[i].getSeatPos().x) {
					activePassengers[i].setInitPos(vec2(activePassengers[i].getSeatPos().x, newPos.y));
				}
				else {
					activePassengers[i].setInitPos(newPos);
				}
				activePassengers[i].setRotation(90.0f);
			}
			// if passenger is neither to the left or right of the row, he haf found it, setting rowFound to true!
			else {
				activePassengers[i].setInitPos(vec2(activePassengers[i].getSeatPos().x, tempInitPos.y));
				activePassengers[i].setIsRowFound(true);

			// TODO: move this outside into seperate elseif 

				if (activePassengers[i].getBaggageTimerStart() < 0) {	//Sets timer when passenger starts to enter the seat row
					activePassengers[i].setIsRowFound(true);
					activePassengers[i].setBaggageTimerStart(glutGet(GLUT_ELAPSED_TIME)); // TODO: implement system time, instead of 'GLUT time'
				}
			}
		}
		//When row found, walk up or down to get in the seat
		else {	
			vec2 tempPos = tempInitPos + vec2(0.0f, tempSpeed);
			if (activePassengers[i].getBaggageTimerStart() < 0) {	//Sets timer when passenger starts to enter the seat row
				activePassengers[i].setBaggageTimerStart(glutGet(GLUT_ELAPSED_TIME));
			}
			else if ((glutGet(GLUT_ELAPSED_TIME) - activePassengers[i].getBaggageTimerStart()) < 1000) {	//If passenger waits less than one second
				//Do nothing
			}

			// else if the passenger is below its seat, walk up
			else if (tempInitPos.y < activePassengers[i].getSeatPos().y) {
				vec2 tempPos = tempInitPos + vec2(0.0f, tempSpeed);

				// if the passenger has overshot the seat, line him up on the seat!
				if (tempPos.y >= activePassengers[i].getSeatPos().y) {
					activePassengers[i].setInitPos(vec2(tempPos.x, activePassengers[i].getSeatPos().y));
				}
				else {
					activePassengers[i].setInitPos(tempInitPos + vec2(0.0f, tempSpeed));
				}
				activePassengers[i].setRotation(0.0f);
			}
			// else if the passenger is above its seat, walk down 
			else if (tempInitPos.y > activePassengers[i].getSeatPos().y) {
				vec2 tempPos = tempInitPos + vec2(0.0f, -tempSpeed);

				// if the passenger has overshot the seat, line him up on the seat!
				if (tempPos.y <= activePassengers[i].getSeatPos().y) {
					activePassengers[i].setInitPos(vec2(tempPos.x, activePassengers[i].getSeatPos().y));
				}
				else {
					activePassengers[i].setInitPos(tempInitPos + vec2(0.0f, -tempSpeed));
				}
				activePassengers[i].setRotation(180.0f);
			}
		}
	}
}