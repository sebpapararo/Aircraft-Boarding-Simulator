#include "Aircraft.h"

// AirbusA319 constructor
// https://www.seatguru.com/airlines/EasyJet_Airlines/easyJet_Airlines_Airbus_A319.php
AirbusA319::AirbusA319() {
	templateName = "Airbus A319";
	noOfRows = 26;
	noOfColumns = 6;
	float rowMove = 0.0f;				// Initial row position
	float rowMoveIncrement = 10.0f;		// Space between rows
	float exitGap = 20.0f;				// Space between emergency row and normal row
	aislePosY = { 35.0f };
	float x = -145.0f;					// x coordinate of the left most row

	float y1 = 50.0f;					// y coordinate of 1st column
	float y2 = 45.0f;
	float y3 = 40.0f;

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

	doorPos.push_back({ vec2(-155.0f, 55.0f), vec2(-155.0f, 15.0f) });	//Index 0, front right and left doors
	doorPos.push_back({ vec2(135.0f, 55.0f), vec2(135.0f, 15.0f) });		//Index 1, rear right and left doors

	wallPos = { vec2(-180.0f, 15.0f),  vec2(-160.0f, 15.0f),  vec2(-150.0f, 15.0f),  vec2(-57.0f, 15.0f),  vec2(-48.0f, 15.0f),  vec2(-42.0f, 15.0f),  vec2(-33.0f, 15.0f),  vec2(130.0f, 15.0f),  vec2(140.0f, 15.0f),  vec2(150.0f, 15.0f),
				vec2(-180.0f, 55.0f),  vec2(-160.0f, 55.0f),  vec2(-150.0f, 55.0f),  vec2(-57.0f, 55.0f),  vec2(-48.0f, 55.0f),  vec2(-42.0f, 55.0f),  vec2(-33.0f, 55.0f),  vec2(130.0f, 55.0f),  vec2(140.0f, 55.0f),  vec2(150.0f, 55.0f) };
}


// Boeing 737-800 constructor
// https://www.seatguru.com/airlines/Thomson_Airways/Thomson_Airways_Boeing_737-800.php
Boeing737::Boeing737() {
	templateName = "Boeing 737-800";
	noOfRows = 32;
	noOfColumns = 6;
	float rowMove = 0.0f;				// Initial row position
	float rowMoveIncrement = 10.0f;		// Space between rows
	float exitGap = 20.0f;				// Space between emergency row and normal row
	aislePosY = { 35.0f };					// y coordinate of the aisle
	float x = -165.0f;					// x coordinate of the left most row

	float y1 = 50.0f;					// y coordinate of 1st column
	float y2 = 45.0f;
	float y3 = 40.0f;

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

	doorPos.push_back({ vec2(-175.0f, 55.0f), vec2(-175.0f, 15.0f) });	//Index 0, front right and left doors
	doorPos.push_back({ vec2(175.0f, 55.0f), vec2(175.0f, 15.0f) });		//Index 1, rear right and left doors

	wallPos = { vec2(-205.0f, 15.0f),  vec2(-180.0f, 15.0f),  vec2(-170.0f, 15.0f),  vec2(-31.0f, 15.0f),  vec2(-19.0f, 15.0f),  vec2(-11.0f, 15.0f),  vec2(1.0f, 15.0f),  vec2(170.0f, 15.0f), vec2(180.0f, 15.0f), vec2(200.0f, 15.0f),
				vec2(-205.0f, 55.0f),  vec2(-180.0f, 55.0f),  vec2(-170.0f, 55.0f),  vec2(-31.0f, 55.0f),  vec2(-19.0f, 55.0f),  vec2(-11.0f, 55.0f),  vec2(1.0f, 55.0f),  vec2(170.0f, 55.0f), vec2(180.0f, 55.0f), vec2(200.0f, 55.0f) };
}


// Boeing 767-300ER constructor
// https://www.seatguru.com/airlines/Thomson_Airways/Thomson_Airways_Boeing_767-300ER_V4.php
Boeing767_300ER::Boeing767_300ER() {
	templateName = "Boeing 767-300ER";
	noOfRows = 45;
	noOfColumns = 8;
	float rowMove = 0.0f;				// Initial row position
	float rowMoveIncrement = 10.0f;		// Space between rows
	float exitGap = 20.0f;				// Space between emergency row and normal row
	aislePosY = { 50.0f, 25.0f };		// y coordinate of the aisle
	float x = -245.0f;					// x coordinate of the left most row

	float y1 = 60.0f;					// y coordinate of 1st column
	float y2 = 55.0f;

	float y3 = 45.0f;
	float y4 = 40.0f;
	float y5 = 35.0f;
	float y6 = 30.0f;

	float y7 = 20.0f;
	float y8 = 15.0f;

	layout.push_back({ vec2(x + rowMove, y3), vec2(x + rowMove, y4), vec2(x + rowMove, y5), vec2(x + rowMove, y6) });
	rowMove += rowMoveIncrement;

	for (int i = 0; i < 11; i++) {
		layout.push_back({ vec2(x + rowMove - 2.5f, y1), vec2(x + rowMove - 2.5f, y2), vec2(x + rowMove, y3), vec2(x + rowMove, y4), vec2(x + rowMove, y5), vec2(x + rowMove, y6), vec2(x + rowMove - 2.5f, y7), vec2(x + rowMove - 2.5f, y8) });
		rowMove += rowMoveIncrement;
	}

	layout.push_back({ vec2(x + rowMove, y3), vec2(x + rowMove, y4), vec2(x + rowMove, y5), vec2(x + rowMove, y6) });
	rowMove += exitGap;

	for (int i = 0; i < 2; i++) {
		layout.push_back({vec2(x + rowMove, y3 - 2.5f), vec2(x + rowMove, y4 - 2.5f), vec2(x + rowMove, y5 - 2.5f) });
		rowMove += rowMoveIncrement;
	}

	for (int i = 0; i < 15; i++) {
		layout.push_back({ vec2(x + rowMove, y1), vec2(x + rowMove, y2), vec2(x + rowMove, y3), vec2(x + rowMove, y4), vec2(x + rowMove, y5), vec2(x + rowMove, y6), vec2(x + rowMove, y7), vec2(x + rowMove, y8) });
		rowMove += rowMoveIncrement;
	}

	layout.push_back({ vec2(x + rowMove, y3), vec2(x + rowMove, y4), vec2(x + rowMove, y5), vec2(x + rowMove, y6) });
	rowMove += exitGap + rowMoveIncrement;

	layout.push_back({ vec2(x + rowMove, y3), vec2(x + rowMove, y4), vec2(x + rowMove, y5), vec2(x + rowMove, y6) });
	rowMove += rowMoveIncrement;

	for (int i = 0; i < 12; i++) {
		layout.push_back({ vec2(x + rowMove, y1), vec2(x + rowMove, y2), vec2(x + rowMove, y3), vec2(x + rowMove, y4), vec2(x + rowMove, y5), vec2(x + rowMove, y6), vec2(x + rowMove, y7), vec2(x + rowMove, y8) });
		rowMove += rowMoveIncrement;
	}

	layout.push_back({ vec2(x + rowMove, y3), vec2(x + rowMove, y4), vec2(x + rowMove, y5), vec2(x + rowMove, y6) });


	doorPos.push_back({ vec2(-260.0f, 65.0f), vec2(-260.0f, 10.0f) });	//Index 0, front right and left doors
	doorPos.push_back({ vec2(245.0f, 65.0f), vec2(245.0f, 10.0f) });		//Index 1, rear right and left doors

	wallPos = { vec2(-300.0f, 10.0f), vec2(-265.0f, 10.0f), vec2(-255.0f, 10.0f), vec2(-120.0f, 10.0f), vec2(-110.0f, 10.0f), vec2(70.0f, 10.0f), vec2(80.0f, 10.0f), vec2(240.0f, 10.0f), vec2(250.0f, 10.0f),  vec2(300.0f, 10.0f),
				vec2(-300.0f, 65.0f), vec2(-265.0f, 65.0f), vec2(-255.0f, 65.0f), vec2(-120.0f, 65.0f), vec2(-110.0f, 65.0f), vec2(70.0f, 65.0f), vec2(80.0f, 65.0f), vec2(240.0f, 65.0f), vec2(250.0f, 65.0f),  vec2(300.0f, 65.0f) };
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

vector<float> Aircraft::getAislePosY() const {
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
