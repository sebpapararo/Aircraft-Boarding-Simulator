#include "Aircraft.h"

// AirbusA319 constructor
AirbusA319::AirbusA319() {
	templateName = "Airbus A319";
	noOfRows = 26;
	noOfColumns = 6;
	float rowMove = 0.0f;				// Initial row position
	float rowMoveIncrement = 10.0f;		// Space between rows
	float exitGap = 15.0f;				// Space between emergency row and normal row
	float x = -145.0f;					// x coordinate of the left most row
	float y1 = 50.0f;					// y coordinate of 1st column
	float y2 = 45.0f;
	float y3 = 40.0f;
	aislePosY = 35.0f;
	float y4 = 30.0f;
	float y5 = 25.0f;
	float y6 = 20.0f;

	for (int i = 0; i < 9; i++) {
		layout.push_back({ vec2(x + rowMove, y1), vec2(x + rowMove, y2), vec2(x + rowMove, y3), vec2(x + rowMove, y4), vec2(x + rowMove, y5), vec2(x + rowMove, y6) });
		rowMove += rowMoveIncrement;
	}

	rowMove += -rowMoveIncrement + exitGap;
	layout.push_back({ vec2(x + rowMove, y1), vec2(x + rowMove, y2), vec2(x + rowMove, y3), vec2(x + rowMove, y4), vec2(x + rowMove, y5), vec2(x + rowMove, y6) });
	rowMove += exitGap;

	for (int i = 0; i < 16; i++) {
		layout.push_back({ vec2(x + rowMove, y1), vec2(x + rowMove, y2), vec2(x + rowMove, y3), vec2(x + rowMove, y4), vec2(x + rowMove, y5), vec2(x + rowMove, y6) });
		rowMove += rowMoveIncrement;
	}

	doorPos.push_back({ vec2(-155.0f, 55.0f), vec2(-155.0f, 5.0f) });	//Index 0, front right and left doors
	doorPos.push_back({ vec2(130.0f, 55.0f), vec2(130.0f, 5.0f) });		//Index 1, rear right and left doors

	wallPos = { vec2(-180.0f, 15.0f),  vec2(-160.0f, 15.0f),  vec2(-150.0f, 15.0f),  vec2(-62.0f, 15.0f),  vec2(-53.0f, 15.0f),  vec2(-47.0f, 15.0f),  vec2(-38.0f, 15.0f),  vec2(125.0f, 15.0f),  vec2(135.0f, 15.0f),  vec2(145.0f, 15.0f),
				vec2(-180.0f, 55.0f),  vec2(-160.0f, 55.0f),  vec2(-150.0f, 55.0f),  vec2(-62.0f, 55.0f),  vec2(-53.0f, 55.0f),  vec2(-47.0f, 55.0f),  vec2(-38.0f, 55.0f),  vec2(125.0f, 55.0f),  vec2(135.0f, 55.0f),  vec2(145.0f, 55.0f) };
}


// Boeing 737-800 constructor
// https://www.seatguru.com/airlines/Thomson_Airways/Thomson_Airways_Boeing_737-800.php
Boeing737::Boeing737() {
	templateName = "Boeing 737-800";
	noOfRows = 32;
	noOfColumns = 6;
	float rowMove = 0.0f;				// Initial row position
	float rowMoveIncrement = 10.0f;		// Space between rows
	float exitGap = 15.0f;				// Space between emergency row and normal row
	float x = -165.0f;					// x coordinate of the left most row
	float y1 = 50.0f;					// y coordinate of 1st column
	float y2 = 45.0f;
	float y3 =40.0f;
	aislePosY = 35.0f;					// y coordinate of the aisle
	float y4 = 30.0f;
	float y5 = 25.0f;
	float y6 = 20.0f;

	for (int i = 0; i < 14; i++) {
		if (i == 0) {		// The first row only has 3 seats on the left of the plane
			layout.push_back({ vec2(x + rowMove, y4), vec2(x + rowMove, y5), vec2(x + rowMove, y6) });
		}
		else {
			layout.push_back({ vec2(x + rowMove, y1), vec2(x + rowMove, y2), vec2(x + rowMove, y3), vec2(x + rowMove, y4),
								vec2(x + rowMove, y5), vec2(x + rowMove, y6) });
		}
		rowMove += rowMoveIncrement;	
	}

	rowMove += -rowMoveIncrement + exitGap;
	layout.push_back({ vec2(x + rowMove, y1), vec2(x + rowMove, y2), vec2(x + rowMove, y3), vec2(x + rowMove, y4),
								vec2(x + rowMove, y5), vec2(x + rowMove, y6) });
	rowMove += exitGap;

	for (int i = 0; i < 17; i++) {
		layout.push_back({ vec2(x + rowMove, y1), vec2(x + rowMove, y2), vec2(x + rowMove, y3), vec2(x + rowMove, y4),
								vec2(x + rowMove, y5), vec2(x + rowMove, y6) });
		rowMove += rowMoveIncrement;
	}

	doorPos.push_back({ vec2(-175.0f, 55.0f), vec2(-175.0f, 5.0f) });	//Index 0, front right and left doors
	doorPos.push_back({ vec2(165.0f, 55.0f), vec2(165.0f, 5.0f) });		//Index 1, rear right and left doors

	wallPos = { vec2(-185.0f, 15.0f),  vec2(-179.0f, 15.0f),  vec2(-171.0f, 15.0f),  vec2(-31.0f, 15.0f),  vec2(-24.0f, 15.0f),  vec2(-16.0f, 15.0f),  vec2(-9.0f, 15.0f),  vec2(162.0f, 15.0f), vec2(168.0f, 15.0f), vec2(190.0f, 15.0f),
				vec2(-185.0f, 55.0f),  vec2(-179.0f, 55.0f),  vec2(-171.0f, 55.0f),  vec2(-31.0f, 55.0f),  vec2(-24.0f, 55.0f),  vec2(-16.0f, 55.0f),  vec2(-9.0f, 55.0f),  vec2(162.0f, 55.0f), vec2(168.0f, 55.0f), vec2(190.0f, 55.0f) };
}



/********* Other methods *********/

vector<vector<vec2>> Aircraft::getTemplate() const {
	return layout;
}

int Aircraft::getNoOfRows() const {
	return noOfRows;
}

int Aircraft::getNoOfColumns() const {
	return noOfColumns;
}

float Aircraft::getAislePosY() const {
	return aislePosY;
}

std::string Aircraft::getTemplateName() const {
	return templateName;
}

vector<vector<vec2>> Aircraft::getDoorPos() const {
	return doorPos;
}

vector<vec2> Aircraft::getWallPos() const {
	return wallPos;
}
