#include "Passenger.h"

Passenger::Passenger(vec2 pos, vec2 init, bool isRight) {
	seatPos = pos;
	initPos = init;
	isWalkingRight = isRight;
}

vec2 Passenger::getSeatPos() const {
	return seatPos;
}
void Passenger::setSeatPos(vec2 pos){
	seatPos = pos;
}

vec2 Passenger::getInitPos() const {
	return initPos;
}
void Passenger::setInitPos(vec2 init) {
	initPos = init;
}

float Passenger::getAisleY() const {
	return aisleY;
}
void Passenger::setAisleY(float y) {
	aisleY = y;
}

float Passenger::getMaxSpeed() const {
	return maxSpeed;
}
void Passenger::setMaxSpeed(float speed) {
	maxSpeed = speed;
}

float Passenger::getCurrSpeed() const {
	return currSpeed;
}
void Passenger::setCurrSpeed(float speed) {
	currSpeed = speed;
}

float Passenger::accelerate() {
	if (currSpeed < maxSpeed) {
		currSpeed += 0.4f;
		return currSpeed;
	}
	else {
		return currSpeed;
	}
}
float Passenger::decelerate() {
	if (currSpeed > 0.0f) {
		currSpeed -= 2.0f;
		if (currSpeed < 0.0f) {
			currSpeed = 0.0f;
		}
		return currSpeed;
	}
	else {
		return currSpeed;
	}
}
float Passenger::stop() {
	float temp = currSpeed;
	currSpeed = 0.0f;
	return temp;
}

bool Passenger::getIsWalkingRight() const {
	return isWalkingRight;
}
void Passenger::setIsWalkingRight(bool isRight) {
	isWalkingRight = isRight;
}

bool Passenger::getIsYAlignedWithAisle() const {
	return isYAlignedWithAisle;
}
void Passenger::setIsYAlignedWithAisle(bool isLinedUp) {
	isYAlignedWithAisle = isLinedUp;
}

bool Passenger::getIsRowFound() const {
	return isRowFound;
}
void Passenger::setIsRowFound(bool isFound) {
	isRowFound = isFound;
}

float Passenger::getBaggageTimerStart() const {
	return baggageTimerStart;
}
void Passenger::setBaggageTimerStart(float time) {
	baggageTimerStart = time;
}

float Passenger::getRotation() const {
	return rotation;
}
void Passenger::setRotation(float newRotation) {
	rotation = newRotation;
}