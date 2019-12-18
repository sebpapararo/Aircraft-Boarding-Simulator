#pragma once
#include "Passenger.h"
#include "GraphicsEngine.h"
#include <glut/glut.h>  // GLUT, include glu.h and gl.h

#include <vector>
using std::vector;

class PhysicsEngine {
public:
	void updatePositions(vector<Passenger> &activePassengers, vector<Passenger> &activeSeatedPassengers, vector<float> aislePosY, double startTime);
	double getAverageSeatedTime();

private:
	float passengerRadius = 2.0f;	//Collision detection
	double totalSeatedTime = 0.0f;
	double averageSeatedTime = 0.0f;
};