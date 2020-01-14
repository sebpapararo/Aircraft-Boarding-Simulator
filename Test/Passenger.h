#pragma once
#include "glm\glm.hpp"

using glm::vec2;

class Passenger {
public:
	Passenger(vec2 pos, vec2 init, bool isRight);
	vec2 getSeatPos() const;
	void setSeatPos(vec2 pos);
	vec2 getInitPos() const;
	void setInitPos(vec2 init);
	float getAisleY() const;
	void setAisleY(float y);

	float getMaxSpeed() const;
	void setMaxSpeed(float speed);
	float getCurrSpeed() const;
	void setCurrSpeed(float speed);
	float accelerate();
	float decelerateToSlow();
	float stop();

	bool getIsWalkingRight() const;
	void setIsWalkingRight(bool isRight);
	bool getIsYAlignedWithAisle() const;
	void setIsYAlignedWithAisle(bool isLinedUp);
	bool getIsRowFound() const;
	void setIsRowFound(bool isFound);
	float getBaggageTimerStart() const;
	void setBaggageTimerStart(float time);
	float getRotation() const;
	void setRotation(float newRotation);

private:
	vec2 seatPos;
	vec2 initPos;
	float aisleY;
	// 12 is equivalent to 1 meter per second
	float maxSpeed = 12.0f;
	float currSpeed = 0.0f;
	bool isYAlignedWithAisle = false;
	bool isRowFound = false;
	float baggageTimerStart;
	bool isWalkingRight;
	float rotation = 90.0f;
};