#pragma once
#include "Passenger.h"
#include "GraphicsEngine.h"
#include <glut/glut.h>  // GLUT, include glu.h and gl.h

#include <vector>
using std::vector;

class PhysicsEngine {
public:
	float passengerRadius = 2.0f;	//Collision detection
	void seatedPassengerPercentage(vector<Passenger> &activeSeatedPassengers, int noOfPassengers);
	void updatePositions(vector<Passenger> &activePassengers, vector<Passenger> &activeSeatedPassengers, float aislePosY);
};