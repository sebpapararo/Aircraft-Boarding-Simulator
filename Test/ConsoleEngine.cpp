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
	// Select which aircraft you want to run the simulation
	// Choose from: 'AirbusA319' | 'Boeing737'
	c_selectedAircraft = Boeing737();

	// Get information from the template
	c_aircraftName = c_selectedAircraft.getTemplateName();
	c_activeTemplate = c_selectedAircraft.getTemplate();
	c_activeDoorPos = c_selectedAircraft.getDoorPos();
	c_noOfRows = c_selectedAircraft.getNoOfRows();
	c_noOfColumns = c_selectedAircraft.getNoOfColumns();
	c_aislePosY = c_selectedAircraft.getAislePosY();
	c_activeWallPos = c_selectedAircraft.getWallPos();

	// Generate passengers
	c_SS.randomSeat(c_currentAlgorithm, c_noOfRows, c_noOfColumns, c_aircraftName, c_activeTemplate, c_activeDoorPos, c_activePassengers);
}


void ConsoleEngine::runConsoleEngine() {

	// Initialise everything needed for the simulation
	init();

	clock_t startTimer = clock();
	std::cout << "Starting the simulation!" << std::endl;
	int logicCycles = 0;
	
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