#include "Passenger.h"

Passenger::Passenger(vec2 pos, vec2 init) {
	seatPos = pos;
	initPos = init;
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

float Passenger::getWalkingSpeed() const {
	return walkingSpeed;
}

void Passenger::setWalkingSpeed(float speed) {
	walkingSpeed = speed;
}

bool Passenger::getIsAligned() const {
	return isAligned;
}

void Passenger::setIsAligned(bool isLinedUp) {
	isAligned = isLinedUp;
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