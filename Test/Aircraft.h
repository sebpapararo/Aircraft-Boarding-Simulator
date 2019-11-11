#pragma once
#include "Image_Loading/glew.h"
#include <string>
#include <vector>
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "glm\gtc\matrix_inverse.hpp"

using std::vector;
using glm::vec2;

class Aircraft {
public:
	vector<vector<vec2>> getTemplate();
	int getNoOfRows();
	int getNoOfColumns();
	float getAislePosY();
	std::string getTemplateName();
	vector<vector<vec2>> getDoorPos();
	vector<vec2> getWallPos();

protected:
	float aislePosY;
	int noOfRows;
	int noOfColumns; // Note: this is also the max number of seats in any row
	std::string templateName;
	vector<vector<vec2>> layout;
	vector<vector<vec2>> doorPos;
	vector<vec2> wallPos;
};

class AirbusA319 : public Aircraft {
public:
	AirbusA319();
};

class Boeing737 : public Aircraft{
public:
	Boeing737();
};