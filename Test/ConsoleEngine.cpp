#include "ConsoleEngine.h"

Aircraft c_selectedAircraft;
std::string c_aircraftName;

vector<vector<vec2>> c_activeTemplate;
vector<vector<vec2>> c_activeDoorPos;
int c_noOfRows;
int c_noOfColumns;
vector<Passenger> c_activePassengers;
vector<Passenger> c_activeSeatedPassengers;
vector<float> c_aislePosY;
vector<vec2> c_activeWallPos;
std::string c_currentAlgorithm;

PhysicsEngine c_PE;
SeatingStrategies c_SS;

void ConsoleEngine::init() {
	// Ask the user which plane template they want to use
	int planeChoice;
	std::cout << "\nWhich plane template would you like to use?" << std::endl;
	std::cout << "Airbus A319 (1), Airbus A321neo (2), Airbus A380-800 (3), Boeing 737-800 (4), or Boeing 767-300ER (5)." << std::endl;
	std::cout << "Enter the number corresponding to your choice: ";
	std::cin >> planeChoice;

	// Let the user try again if entered an invalid number
	while (planeChoice < 1 || planeChoice > 5) {
		std::cout << "Invalid number. Please enter '1' for Airbus A319, '2' for Airbus A321neo, '3' for Airbus A380-800, '4' for Boeing 737-800 or '5' for Boeing 767-300ER: ";
		std::cin >> planeChoice;
	}

	// Set the selected aircraft
	switch (planeChoice) {
		case 1:
			c_selectedAircraft = AirbusA319();
			break;
		case 2:
			c_selectedAircraft = AirbusA321neo();
			break;
		case 3:
			c_selectedAircraft = AirbusA380_800();
			break;
		case 4:
			c_selectedAircraft = Boeing737();
			break;
		case 5:
			c_selectedAircraft = Boeing767_300ER();
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
	std::cout << "Back-to-Front (1), Inside-Out (2), Outside-In (3), Seat-by-Seat (4), Random (5) or Row-by-Row (6)" << std::endl;
	std::cout << "Enter the number corresponding to your choice: ";
	std::cin >> algorithmChoice;

	// Let the user try again if entered an invalid number
	while (algorithmChoice != 1 && algorithmChoice != 2 && algorithmChoice != 3 && algorithmChoice != 4) {
		std::cout << "Invalid number. Please enter '1' for Back-to-Front, '2' for Inside-Out, '3' for Outside-In, '4' for Seat-by-Seat, '5' for Random or '6' for Row-by-Row: ";
		std::cin >> algorithmChoice;
	}

	// Ask the user what doors to use for boarding
	int activeDoorsChoice;
	std::cout << "\nWhich aircraft doors would you like to use?" << std::endl;
	std::cout << "Rear (1), Front (2), Front and Rear (3)" << std::endl;
	std::cout << "Enter the number corresponding to your choice: ";
	std::cin >> activeDoorsChoice;

	// Let the user try again if entered an invalid number
	while (activeDoorsChoice < 1 || activeDoorsChoice > 3) {
		std::cout << "Invalid number. Please enter '1' for Rear, '2' for Front, or '3' for Front and rear doors: ";
		std::cin >> activeDoorsChoice;
	}

	// Generate passengers for the chosen boarding algorithm
	switch (algorithmChoice) {
		case 1:
			c_SS.backToFront(c_currentAlgorithm, c_noOfRows, c_activeTemplate, c_activeDoorPos, activeDoorsChoice, c_activePassengers, c_aislePosY);
			break;
		case 2:
			c_SS.insideOut(c_currentAlgorithm, c_noOfRows, c_activeTemplate, c_activeDoorPos, activeDoorsChoice, c_activePassengers, c_aislePosY);
			break;
		case 3:
			c_SS.outsideIn(c_currentAlgorithm, c_noOfRows, c_activeTemplate, c_activeDoorPos, activeDoorsChoice, c_activePassengers, c_aislePosY);
			break;
		case 4:
			c_SS.seatBySeat(c_currentAlgorithm, c_noOfRows, c_noOfColumns, c_aircraftName, c_activeTemplate, c_activeDoorPos, activeDoorsChoice, c_activePassengers, c_aislePosY);
			break;
		case 5:
			c_SS.randomSeat(c_currentAlgorithm, c_noOfRows, c_noOfColumns, c_aircraftName, c_activeTemplate, c_activeDoorPos, activeDoorsChoice, c_activePassengers, c_aislePosY);
			break;
		case 6:
			c_SS.rowByRow(c_currentAlgorithm, c_noOfRows, c_activeTemplate, c_activeDoorPos, activeDoorsChoice, c_activePassengers, c_aislePosY);
			break;
	}
}

void ConsoleEngine::runConsoleEngine() {

	// Initialise simulation parameters via user inputs
	init();

	int totalPassengers = c_activePassengers.size();

	std::cout << "\nRunning the simulation!..." << std::endl;
	clock_t startTimer = clock();
	
	//Runs the simulation until all passengers are seated
	while (!c_activePassengers.empty()) {
		c_PE.updatePositions(c_activePassengers, c_activeSeatedPassengers, c_aislePosY, startTimer);
	}
	
	//Displays simulation results
	clock_t totalRuntime = clock();
	std::cout << "All passengers are seated." << std::endl;
	std::cout << "The algorithm used was: '" << c_currentAlgorithm << "' and the plane template was: '" << c_aircraftName << "'" << std::endl;
	std::cout << "Total number of seats/passengers was: " + totalPassengers << std::endl;
	std::cout << "Everyone is seated. The total runtime was (in seconds): " << (totalRuntime - startTimer) / (double)CLOCKS_PER_SEC << std::endl;
	std::cout << "Everyone is seated. Average time to be seated was (in seconds): " << c_PE.getAverageSeatedTime() / (double)CLOCKS_PER_SEC << std::endl;
}