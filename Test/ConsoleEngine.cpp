#include "ConsoleEngine.h"

Aircraft c_selectedAircraft;
std::string c_aircraftName;

vector<vector<vec2>> c_activeTemplate;
vector<vector<vec2>> c_activeDoorPos;
int c_noOfRows;
int c_noOfColumns;
vector<Passenger> c_activePassengers;
vector<Passenger> c_activeSeatedPassengers;
float c_aislePosY;
vector<vec2> c_activeWallPos;
std::string c_currentAlgorithm;

PhysicsEngine c_PE;
SeatingStrategies c_SS;

void ConsoleEngine::init() {
	// Ask the user which plane template they want to use
	int planeChoice;
	std::cout << "\nWhich plane template would you like to use? Airbus A319 (1) or Boeing 737-800 (2)." << std::endl;
	std::cout << "Please enter the number corresponding to your choice: ";
	std::cin >> planeChoice;

	// Let the user try again if entered an invalid number
	while (planeChoice != 1 && planeChoice != 2) {
		std::cout << "Sorry, invalid number. Please enter '1' for the Airbus A319 or '2' for the Boeing 737-800: ";
		std::cin >> planeChoice;
	}

	// Set the selected aircraft
	switch (planeChoice) {
		case 1:
			c_selectedAircraft = AirbusA319();
			break;
		case 2:
			c_selectedAircraft = Boeing737();
			break;
	}
	
	// Get information from the template
	c_aircraftName = c_selectedAircraft.getTemplateName();
	c_activeTemplate = c_selectedAircraft.getTemplate();
	c_activeDoorPos = c_selectedAircraft.getDoorPos();
	c_noOfRows = c_selectedAircraft.getNoOfRows();
	c_noOfColumns = c_selectedAircraft.getNoOfColumns();
	c_aislePosY = c_selectedAircraft.getAislePosY();
	c_activeWallPos = c_selectedAircraft.getWallPos();

	
	// Ask the user what boarding algorithm they want to use
	int algorithmChoice;
	std::cout << "\nWhich boarding strategy would you like to use?" << std::endl;
	std::cout << "back-to-front (1), seat-by-seat (2), row-by-row (3) or random-seat (4)" << std::endl;
	std::cout << "Please enter the number corresponding to your choice: ";
	std::cin >> algorithmChoice;

	// Let the user try again if entered an invalid number
	while (algorithmChoice != 1 && algorithmChoice != 2 && algorithmChoice != 3 && algorithmChoice != 4) {
		std::cout << "Sorry, invalid number. Please enter '1' for back-to-front, '2' for seat-by-seat, '3' for row-by-row or '4' for random-seat: ";
		std::cin >> algorithmChoice;
	}

	// Generate passengers for the chosen boarding algorithm
	switch (algorithmChoice) {
		case 1:
			c_SS.backToFront(c_currentAlgorithm, c_noOfRows, c_activeTemplate, c_activeDoorPos, c_activePassengers);
			break;
		case 2:
			c_SS.seatBySeat(c_currentAlgorithm, c_noOfRows, c_noOfColumns, c_aircraftName, c_activeTemplate, c_activeDoorPos, c_activePassengers);
			break;
		case 3:
			c_SS.rowByRow(c_currentAlgorithm, c_noOfRows, c_activeTemplate, c_activeDoorPos, c_activePassengers);
			break;
		case 4:
			c_SS.randomSeat(c_currentAlgorithm, c_noOfRows, c_noOfColumns, c_aircraftName, c_activeTemplate, c_activeDoorPos, c_activePassengers);
			break;
	}
}

void ConsoleEngine::runConsoleEngine() {

	// Initialise everything needed for the simulation
	init();

	std::cout << "\nStarting the simulation!" << std::endl;
	int logicCycles = 0;
	clock_t startTimer = clock();
	
	while (!c_activePassengers.empty()) {
		c_PE.updatePositions(c_activePassengers, c_activeSeatedPassengers, c_aislePosY);
		logicCycles++;
	}
		
	clock_t totalRuntime = clock();
	std::cout << "All passengers are now seated!" << std::endl;
	std::cout << "The algorithm used was: '" << c_currentAlgorithm << "' and the plane template was: '" << c_aircraftName << "'" << std::endl;
	std::cout << "Everyone is now seated! The total runtime was (seconds): " << totalRuntime / (double)CLOCKS_PER_SEC << std::endl;
	std::cout << "Everyone is now seated! The total runtime was (logic cycles): " << logicCycles << std::endl;
}