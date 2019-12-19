#pragma once
#include <string>
#include <vector>
#include "glm\glm.hpp"

using std::vector;
using glm::vec2;

class Aircraft {
public:
	vector<vector<vec2>> getTemplate() const;
	int getNoOfRows() const;
	int getNoOfColumns() const;
	vector<float> getAislePosY() const;
	std::string getTemplateName() const;
	vector<vector<vec2>> getDoorPos() const;
	vector<vec2> getWallPos() const;

protected:
	vector<float> aislePosY;
	int noOfRows;
	int noOfColumns;			// Note: this is also the max number of seats in any row
	std::string templateName;
	vector<vector<vec2>> layout;
	vector<vector<vec2>> doorPos;
	vector<vec2> wallPos;
};

class AirbusA319 : public Aircraft {
public:
	AirbusA319();
};

class AirbusA321neo : public Aircraft {
public:
	AirbusA321neo();
};

class AirbusA380_800 : public Aircraft {
public:
	AirbusA380_800();
};

class Boeing737 : public Aircraft{
public:
	Boeing737();
};

class Boeing767_300ER : public Aircraft {
public:
	Boeing767_300ER();
};