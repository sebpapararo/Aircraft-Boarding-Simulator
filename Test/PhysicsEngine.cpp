#include "PhysicsEngine.h"

#include <chrono>

// Defining types
typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::milliseconds ms;
typedef std::chrono::duration<float> fsec;

auto lastDelta = Time::now();
auto currentDelta = Time::now();
bool firstLoop = true;


const float faceUp = 0.0;
const float faceLeft = 90.0;
const float faceDown = 180.0;
const float faceRight = 270.0;



// parameters, how far they can move, passenger
float PhysicsEngine::moveToWaypoint(float tempSpeed, Passenger &p, vector<Passenger> &activePassengers, vector<Passenger> &activeSeatedPassengers, float passengerRadius, float aislePosY, int passengerNo) {
	//std::cout << " moving to waypoint" << std::endl;
	// Initialising passanger information
	vec2 tempInitPos = p.getInitPos();
	//float tempSpeed = (activePassengers[i].getWalkingSpeed() * doubleDt);
	float distanceCD = passengerRadius + tempSpeed;
	bool tempIsAisleAligned = p.getIsYAlignedWithAisle();
	bool tempIsWalkingRight = p.getIsWalkingRight();
	std::cout << tempSpeed << std::endl;

	//If passenger is seated, move passenger to activeSeatedPassengers vector and move on to next passenger
	if (tempInitPos == p.getSeatPos()) {
		activeSeatedPassengers.push_back(p);
		activePassengers.erase(activePassengers.begin() + passengerNo);
		return 0;
	}

	// ================== Movement Logic ==================

	//If aligned with the aisle, set to true
	if (tempInitPos.y == aislePosY) {
		p.setIsYAlignedWithAisle(true);
	}

	// TODO: collision detection needs some work, because there position is calculated before checks for overshooting
	//		 happen, collisions may be detected even when they will not occur!

	//Lines up passengers with the aisle
	if (!tempIsAisleAligned) {

		//If below aisle, walk up
		if (tempInitPos.y < aislePosY) {											
			vec2 newPos = tempInitPos + vec2(0.0f, tempSpeed);

			if (tempInitPos.y + distanceCD < aislePosY) {

				// checking each passenger for collision detection: 
				for (size_t j = 0; j < activePassengers.size(); j++) {

					int xd = activePassengers[j].getInitPos().x - newPos.x;
					int yd = activePassengers[j].getInitPos().y - newPos.y;

					// if passenger is in the way, dont move!
					if (activePassengers[j].getInitPos().y > tempInitPos.y && sqrt(xd*xd + yd + yd) < distanceCD) {
						newPos -= vec2(0.0f, tempSpeed);
						return 0;
					}
				}
			}

			// if the passenger has overshot the aisle, line him up on the aisle! TODO: move passengers who have overshot the aisle, into the aisle the distance they overshot!
			if (tempInitPos.y + distanceCD >= aislePosY) {
				// when a passenger has overshot the aisle, move them back to line up with it and move then into the aisle, then return the amount they have left to move
				float overshotDistance = abs((tempInitPos.y + distanceCD) - aislePosY);

				p.setInitPos(vec2(tempInitPos.x, aislePosY));
				p.setIsYAlignedWithAisle(true);
				return overshotDistance;
					
			}
			// otherwise, move passenger to new position, no obstacles or overshooting detected.
			else {
				p.setInitPos(newPos);
				p.setRotation(faceUp);
				return 0;
			}
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
						return 0;
					}
				}
			}
			// if the passenger has overshot the aisle, line him up on the aisle!
			if (tempInitPos.y + distanceCD <= aislePosY) {

				float overshotDistance = abs((tempInitPos.y + distanceCD) - aislePosY);

				p.setInitPos(vec2(tempInitPos.x, aislePosY));
				p.setIsYAlignedWithAisle(true);
				return overshotDistance;
			}

			else {
				p.setInitPos(newPos);
				p.setInitPos(newPos);
				p.setRotation(faceDown);
				return 0;
			}
			p.setRotation(180.0f);
		}
	}
	//Moves passengers to their seat row
	else if (!p.getIsRowFound()) {

		//If to the left of the row, walk right
		if ((tempInitPos.x + 2.0f) < p.getSeatPos().x) { 

			vec2 newPos = tempInitPos + vec2(tempSpeed, 0.0f);

			for (size_t j = 0; j < activePassengers.size(); j++) {	//Collision detection

				if (abs(newPos.x - activePassengers[j].getInitPos().x) < distanceCD &&
					activePassengers[j].getIsYAlignedWithAisle() &&
					passengerNo != j) {
					if (tempIsWalkingRight != activePassengers[j].getIsWalkingRight() &&
						!activePassengers[j].getIsRowFound()) {
						newPos = tempInitPos + vec2(tempSpeed / 4, 0.0f);
						return 0;
					}
					else if (tempInitPos.x > activePassengers[j].getInitPos().x) {
						vec2 newPos = tempInitPos + vec2(tempSpeed, 0.0f);
						return 0;
					}
					else {
						newPos = tempInitPos;
						return 0;
					}
				}

			}

			// if the passenger has overshot the row, line him up on the row!
			if (newPos.x >= p.getSeatPos().x) {

				float overshotDistance = abs(newPos.x - p.getSeatPos().x);
				p.setInitPos(vec2(p.getSeatPos().x, newPos.y));
				p.setRotation(faceRight);
				return overshotDistance;

			}
			else {
				p.setInitPos(newPos);
				p.setRotation(faceRight);
				return 0;
			}
			
		}
		else if ((tempInitPos.x - 2.0f) > p.getSeatPos().x) {	//If to the right of the row, walk left
			vec2 newPos = tempInitPos + vec2(-tempSpeed, 0.0f);
			for (size_t j = 0; j < activePassengers.size(); j++) {	//Collision detection

				if (abs(newPos.x - activePassengers[j].getInitPos().x) < distanceCD &&
					activePassengers[j].getIsYAlignedWithAisle() &&
					passengerNo != j) {
					if (tempIsWalkingRight != activePassengers[j].getIsWalkingRight() &&
						!activePassengers[j].getIsRowFound()) {
						newPos = tempInitPos + vec2(-tempSpeed / 4, 0.0f);
						return 0;
					}
					else if (tempInitPos.x < activePassengers[j].getInitPos().x) {
						vec2 newPos = tempInitPos + vec2(-tempSpeed, 0.0f);
						return 0;
					}
					else {
						newPos = tempInitPos;
						return 0;
					}
				}

			}
			// if the passenger has overshot the row, line him up on the row!
			if (newPos.x <= p.getSeatPos().x) {
				float overshotDistance = abs(newPos.x - p.getSeatPos().x);

				p.setInitPos(vec2(p.getSeatPos().x, newPos.y));
				p.setRotation(faceLeft);
				return overshotDistance;
			}
			else {
				p.setRotation(faceLeft);
				p.setInitPos(newPos);
				return 0;
			}
			
		}
		// if passenger is neither to the left or right of the row, he haf found it, setting rowFound to true!
		else {
			p.setInitPos(vec2(p.getSeatPos().x, tempInitPos.y));
			p.setIsRowFound(true);

			// TODO: move this outside into seperate elseif 

			if (p.getBaggageTimerStart() < 0) {	//Sets timer when passenger starts to enter the seat row
				p.setIsRowFound(true);
				p.setBaggageTimerStart(glutGet(GLUT_ELAPSED_TIME)); // TODO: implement system time, instead of 'GLUT time'
			}
		}
	}
	//When row found, walk up or down to get in the seat
	else {
		vec2 tempPos = tempInitPos + vec2(0.0f, tempSpeed);

		//Sets timer when passenger starts to enter the seat row
		if (p.getBaggageTimerStart() < 0) {	
			p.setBaggageTimerStart(glutGet(GLUT_ELAPSED_TIME));
		}

		//If passenger waits less than one second
		else if ((glutGet(GLUT_ELAPSED_TIME) - p.getBaggageTimerStart()) < 1000) {	
			return 0;
			//Do nothing
		}

		// else if the passenger is below its seat, walk up
		else if (tempInitPos.y < p.getSeatPos().y) {
			vec2 tempPos = tempInitPos + vec2(0.0f, tempSpeed);

			// if the passenger has overshot the seat, line him up on the seat!
			if (tempPos.y >= p.getSeatPos().y) {
				p.setInitPos(vec2(tempPos.x, p.getSeatPos().y));
				p.setRotation(faceLeft);
				return 0;
			}
			else {
				p.setInitPos(tempInitPos + vec2(0.0f, tempSpeed));
				p.setRotation(faceUp);
				return 0;
			}
		}
		// else if the passenger is above its seat, walk down 
		else if (tempInitPos.y > p.getSeatPos().y) {
			vec2 tempPos = tempInitPos + vec2(0.0f, -tempSpeed);

			// if the passenger has overshot the seat, line him up on the seat!
			if (tempPos.y <= p.getSeatPos().y) {
				p.setInitPos(vec2(tempPos.x, p.getSeatPos().y));
				p.setRotation(faceLeft);
				return 0;
			}
			else {
				p.setInitPos(tempInitPos + vec2(0.0f, -tempSpeed));
				p.setRotation(faceDown);
				return 0;
			}
		}
	}
}

// working on overshooting


inline bool isEqual(double x, double y)
{
	const double epsilon = 1e-5 /* some small number such as 1e-5 */;
	return std::abs(x - y) <= epsilon * std::abs(x);
	// see Knuth section 4.2.2 pages 217-218
}

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
	// TODO: add a time wait here
	if (ds.count() == 0) {
		std::cout << " NO TIME PASSED" << std::endl;
		return;
	}

	// For each passenger: 
	for (size_t i = 0; i < activePassengers.size(); i++) {

		float tempSpeed = (activePassengers[i].getWalkingSpeed() * doubleDt);

		float movementLeft = moveToWaypoint(tempSpeed, activePassengers[i], activePassengers, activeSeatedPassengers, passengerRadius, aislePosY, i);

		while (!isEqual(0, movementLeft)) {
			movementLeft = moveToWaypoint(tempSpeed, activePassengers[i], activePassengers, activeSeatedPassengers, passengerRadius, aislePosY, i);
		}

		//float distanceCD = passengerRadius + tempSpeed;
	}

}
