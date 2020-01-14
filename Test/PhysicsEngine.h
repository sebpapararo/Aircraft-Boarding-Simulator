#pragma once
#include "Passenger.h"
#include "GraphicsEngine.h"
#include <glut/glut.h>  // GLUT, include glu.h and gl.h

#include <vector>
using std::vector;

class PhysicsEngine {
private:
	double simSpeed = 10;
    double totalSeatedTime = 0.0f;
	double averageSeatedTime = 0.0f;
    float passengerRadius = 2.0f;	//Collision detection
	
public:
	double getSimSpeed();
	void setSimSpeed(double speed);
    //void updatePositions(vector<Passenger> &activePassengers, vector<Passenger> &activeSeatedPassengers, float aislePosY);
	void updatePositions(vector<Passenger> &activePassengers, vector<Passenger> &activeSeatedPassengers, vector<float> aislePosY, double startTime);
	double getAverageSeatedTime();
	void resetDelta();
	void seatedPassengerPercentage(vector<Passenger> &activeSeatedPassengers, int noOfPassengers);
	
};