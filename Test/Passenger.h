#pragma once
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "glm\gtc\matrix_inverse.hpp"

using glm::vec2;

class Passenger {
public:
	Passenger(vec2 pos, vec2 init);

	vec2 getSeatPos();
	void setSeatPos(vec2 pos);

	vec2 getInitPos();
	void setInitPos(vec2 init);

	float getWalkingSpeed();
	void setWalkingSpeed(float speed);

	bool getIsAligned();
	void setIsAligned(bool isLinedUp);

	bool getIsRowFound();
	void setIsRowFound(bool isFound);

	float getBaggageTimerStart();
	void setBaggageTimerStart(float time);

	float getRotation();
	void setRotation(float newRotation);

private:
	vec2 seatPos;
	vec2 initPos;
	float walkingSpeed = 1.0f;
	bool isAligned = false;
	bool isRowFound = false;
	float baggageTimerStart;
	bool isWalkingRight;
	float rotation = 90.0f;
};