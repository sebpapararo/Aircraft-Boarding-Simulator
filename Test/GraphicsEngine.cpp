#include "GraphicsEngine.h"

int zoom = 0;
float displayX, displayY, spacing;

int window = 0;
bool isConsole = false;
bool isBoarded = false;

//Start screen
bool isStarted = false;
int menuSelect = 1;
int strategySelect = 1;
int actveDoorsSelect = 1;
int mapSelect = 1;

std::string strategiesList[] = { "Back-to-Front", "Centre-Out", "Seat-by-Seat", "Random", "Row-by-Row" };
std::string activeDoorsList[] = { "Rear", "Front", "Front and Rear" };
std::string mapList[] = { "Airbus A319", "Boeing 737-800", "Boeing 767-300ER" };

std::string setStrategyText = "--> Set boarding strategy: ";
std::string setActiveDoorsTest = "Set active doors: ";
std::string setMapText = "Set aircraft map: ";

std::string selectedStrategyText = "Back-to-Front";
std::string selectedDoorsText = "Rear";
std::string selectedMapText = "Airbus A319";

int totalPassengers = 0;

int screenWidth = GetSystemMetrics(SM_CXSCREEN), screenHeight = GetSystemMetrics(SM_CYSCREEN);
float aspect;
bool keys[256];
bool isPressed = false;

//FPS and runtime timing
int FPSCap = 60;
float FPS = 0.0f;
double startTime;
double totalRuntime;
const char* runtimeResultText = "Total runtime (in seconds): ";

//Texture/shape parameters
DrawObjects DO;
GLuint Passenger1 = 0;
GLuint Seat1 = 0;
float passengerHeight = 3.5f;
float passengerWidth = 3.5f;
float seatHeight = 2.0f;
float seatWidth = 3.0f;
char passenger1Path[] = "Textures/Passenger1.png";

Aircraft g_selectedAircraft;
std::string g_aircraftName;

vector<vector<vec2>> g_activeTemplate;
vector<vector<vec2>> g_activeDoorPos;
int g_noOfRows;
int g_noOfColumns;
vector<Passenger> g_activePassengers;
vector<Passenger> g_activeSeatedPassengers;
vector<float> g_aislePosY;
vector<vec2> g_activeWallPos;
std::string g_currentAlgorithm;

PhysicsEngine g_PE;
SeatingStrategies g_SS;


void GraphicsEngine::init() {
	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);

	reshape(screenWidth, screenHeight);

	Passenger1 = DO.loadPNG(passenger1Path);

	startTime = glutGet(GLUT_ELAPSED_TIME);
}

void GraphicsEngine::initSettings(int strategy, int layout, int doorConfig) {

	if (layout == 1) {
		g_selectedAircraft = AirbusA319();
		zoom = 0;
	}
	else if (layout == 2) {
		g_selectedAircraft = Boeing737();
		zoom = 10;
	}
	else {
		g_selectedAircraft = Boeing767_300ER();
		zoom = 60.0f;
	}

	g_aircraftName = g_selectedAircraft.getTemplateName();
	g_activeTemplate = g_selectedAircraft.getTemplate();
	g_activeDoorPos = g_selectedAircraft.getDoorPos();
	g_noOfRows = g_selectedAircraft.getNoOfRows();
	g_noOfColumns = g_selectedAircraft.getNoOfColumns();
	g_activePassengers.clear();
	g_activeSeatedPassengers.clear();
	g_aislePosY = g_selectedAircraft.getAislePosY();
	g_activeWallPos = g_selectedAircraft.getWallPos();
	isBoarded = false;

	if (strategy == 1) {
		g_SS.backToFront(g_currentAlgorithm, g_noOfRows, g_activeTemplate, g_activeDoorPos, doorConfig, g_activePassengers, g_aislePosY);
	}
	else if (strategy == 2) {
		g_SS.centreOut(g_currentAlgorithm, g_noOfRows, g_activeTemplate, g_activeDoorPos, doorConfig, g_activePassengers, g_aislePosY);
	}
	else if (strategy == 3) {
		g_SS.seatBySeat(g_currentAlgorithm, g_noOfRows, g_noOfColumns, g_aircraftName, g_activeTemplate, g_activeDoorPos, doorConfig, g_activePassengers, g_aislePosY);
	}
	else if (strategy == 4) {
		g_SS.randomSeat(g_currentAlgorithm, g_noOfRows, g_noOfColumns, g_aircraftName, g_activeTemplate, g_activeDoorPos, doorConfig, g_activePassengers, g_aislePosY);
	}
	else {
		g_SS.rowByRow(g_currentAlgorithm, g_noOfRows, g_activeTemplate, g_activeDoorPos, doorConfig, g_activePassengers, g_aislePosY);
	}

	totalPassengers = g_activePassengers.size();
}


void GraphicsEngine::display() {
	reshape(screenWidth, screenHeight);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	FPSLock(FPSCap);

	//Menu
	if (!isStarted) {
		infoDisplay("Please use the arrow keys to set simulation settings:", -150.0f, 20.0f);

		infoDisplay(setStrategyText + selectedStrategyText, -150.0f, 0.0f);
		infoDisplay(setActiveDoorsTest + selectedDoorsText, -150.0f, -10.0f);
		infoDisplay(setMapText + selectedMapText, -150.0f, -20.0f);

		infoDisplay("Press 'ENTER' to start the simulation.", -150.0f, -40.0f);
	}
	//Simulation
	else {
		//Passenger navigation
		g_PE.updatePositions(g_activePassengers, g_activeSeatedPassengers, g_aislePosY, startTime);

		if (!isConsole) {
			//Draws seats
			for (int i = 0; i < g_noOfRows; i++) {
				for (size_t j = 0; j < g_activeTemplate[i].size(); j++) {
					DO.loadObject(Seat1, 90.0f, g_activeTemplate[i][j].x, g_activeTemplate[i][j].y, seatHeight, seatWidth, 1.0f, 0.2f, 0.8f, 0.2f);
				}
			}

			//Draws walls as lines
			glColor3f(0.5f, 0.5f, 0.5f);
			glLineWidth(5.0f);
			glBegin(GL_LINES);
			for (size_t i = 0; i < g_activeWallPos.size() - 1; i += 2) {
				glVertex2f(g_activeWallPos[i].x, g_activeWallPos[i].y);
				glVertex2f(g_activeWallPos[i + 1].x, g_activeWallPos[i + 1].y);
			}
			glEnd();

			//Draws seeking passengers
			for (size_t i = 0; i < g_activePassengers.size(); i++) {
				vec2 tempInitPos = g_activePassengers[i].getInitPos();

				if (g_activeDoorPos[1][1].y < tempInitPos.y && g_activeDoorPos[1][0].y > tempInitPos.y) {
					float tempRotation = g_activePassengers[i].getRotation();
					DO.loadObject(Passenger1, tempRotation, tempInitPos.x, tempInitPos.y, passengerHeight, passengerWidth, 1.0f, 1.0f, 1.0f, 1.0f);
				}
			}

			//Draws seated passengerss
			for (size_t i = 0; i < g_activeSeatedPassengers.size(); i++) {
				vec2 tempInitPos = g_activeSeatedPassengers[i].getInitPos();
				DO.loadObject(Passenger1, 90.0f, tempInitPos.x, tempInitPos.y, passengerHeight, passengerWidth, 1.0f, 1.0f, 1.0f, 1.0f);
			}
		}

		//Runtime timing
		if (!g_activePassengers.empty()) {
			double endTime = glutGet(GLUT_ELAPSED_TIME);
			totalRuntime = (endTime - startTime) / 1000;
		}

		if (!isConsole) {
			// Display the current algorithm to the window
			infoDisplay("Boarding strategy: " + g_currentAlgorithm, displayX, displayY);

			infoDisplay("Active door(s): " + selectedDoorsText, displayX, displayY + spacing);

			// Display the current template name to the window
			infoDisplay("Aircraft map: " + g_selectedAircraft.getTemplateName(), displayX, displayY + spacing*2);

			infoDisplay(runtimeResultText + std::to_string(totalRuntime), displayX, displayY + spacing * 3);

			infoDisplay("Total number of seats/passengers: " + std::to_string(totalPassengers), displayX, displayY + spacing * 4);

			if (isBoarded) {
				infoDisplay("Average time to reach a seat (in seconds): " + std::to_string(g_PE.getAverageSeatedTime()), displayX, displayY + spacing * 5);
			}
			else {
				infoDisplay("Average time to reach a seat (in seconds): running...", displayX, displayY + spacing * 5);
			}
		}

		if (g_activePassengers.empty() && !isBoarded) {
			isBoarded = true;
			/*std::cout << "Boarding strategy: " + g_currentAlgorithm << std::endl;
			std::cout << "Aircraft map: " + g_selectedAircraft.getTemplateName() << std::endl;
			std::cout << runtimeResultText + std::to_string(totalRuntime) << std::endl;*/
		}
	}
	glFlush();	//Render now
	glutSwapBuffers();
	glutPostRedisplay();
}


//Locks frame rate to FRAMES_PER_SECOND
void GraphicsEngine::FPSLock(int FPSCap) {
	const int FRAMES_PER_SECOND = FPSCap;
	const int SKIP_TICKS = 1000 / FRAMES_PER_SECOND;
	DWORD next_game_tick = GetTickCount();	//GetTickCount() returns the current number of milliseconds that have elapsed since the system was started
	int sleep_time = 0;
	next_game_tick += SKIP_TICKS;
	sleep_time = next_game_tick - GetTickCount();
	if (sleep_time >= 0) {
		Sleep(sleep_time);
	}
}


////Not working yet
//void GraphicsEngine::displayFPS() {
//	static float tempFPS = 0.0f;
//	static float lastTime = 0.0f;	//Holds time from last frame
//	float currentTime = GetTickCount() * 0.001f;
//	++tempFPS;
//
//	if (currentTime - lastTime > 1.0f)
//	{
//		lastTime = currentTime;
//		FPS = tempFPS;
//		infoDisplay("FPS: " + std::to_string(FPS), -150.0f, 60.0f);
//		//FPS = 0.0f;
//	}
//	else {
//		infoDisplay("FPS: " + std::to_string(FPS- tempFPS), -150.0f, 60.0f);
//	}
//}


//Displays the current lap the player is on
void GraphicsEngine::infoDisplay(std::string outputString, float posX, float posY) {
	std::string aString = outputString;
	const char* string = aString.c_str();

	glColor3f(1, 1, 1);
	glRasterPos2f(posX, posY);
	int length, i;
	length = (int)strlen(string);
	for (i = 0; i < length; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}

void GraphicsEngine::processKeys(unsigned char key, int x, int y) {	//Takes keyboard input
	if (key == VK_ESCAPE) {	//Escape key closes the application
		exit(0);
	}
	if (key == '1') {
		isConsole = true;
	}
	if (key == '2') {
		isConsole = false;
	}
	if (key == VK_RETURN) {
		if (!isStarted) {
			isStarted = true;
			initSettings(strategySelect, mapSelect, actveDoorsSelect);
			startTime = glutGet(GLUT_ELAPSED_TIME);
			if (mapSelect == 1) {
				displayX = -160.0f;
				displayY = -30.0f;
				spacing = -6.0f;
			}
			else if (mapSelect == 2) {
				displayX = -180.0f;
				displayY = -35.0f;
				spacing = -7.0f;
			}
			else if (mapSelect == 3) {
				displayX = -260.0f;
				displayY = -50.0f;
				spacing = -9.0f;
			}
		}
		else {
			isStarted = false;
			zoom = 0;
		}
	}

	/*if (key == '-' && isZoom == true) {
		zoom++;
	}
	if (key == '+' && isZoom == true) {
		zoom--;
	}*/
	
}

void GraphicsEngine::processSpecialKeys(int key, int x, int y) {
	if (!isStarted) {
		if (key == GLUT_KEY_UP) {
			if (menuSelect == 2) {
				menuSelect--;
				setStrategyText = "--> Set boarding strategy: ";
				setActiveDoorsTest = "Set active doors: ";
				setMapText = "Set aircraft map: ";
			}
			else if (menuSelect == 3) {
				menuSelect--;
				setStrategyText = "Set boarding strategy: ";
				setActiveDoorsTest = "--> Set active doors: ";
				setMapText = "Set aircraft map: ";
			}
			else {
				menuSelect = 3;
				setStrategyText = "Set boarding strategy: ";
				setActiveDoorsTest = "Set active doors: ";
				setMapText = "--> Set aircraft map: ";
			}
		}
		else if (key == GLUT_KEY_DOWN) {
			if (menuSelect == 1) {
				menuSelect++;
				setStrategyText = "Set boarding strategy: ";
				setActiveDoorsTest = "--> Set active doors: ";
				setMapText = "Set aircraft map: ";
			}
			else if (menuSelect == 2) {
				menuSelect++;
				setStrategyText = "Set boarding strategy: ";
				setActiveDoorsTest = "Set active doors: ";
				setMapText = "--> Set aircraft map: ";
			}
			else {
				menuSelect = 1;
				setStrategyText = "--> Set boarding strategy: ";
				setActiveDoorsTest = "Set active doors: ";
				setMapText = "Set aircraft map: ";
			}
		}
		else if (key == GLUT_KEY_RIGHT) {
			if (menuSelect == 1) {
				strategySelect++;
				if (strategySelect > (sizeof(strategiesList) / sizeof(strategiesList[0]))) {
					strategySelect = 1;
				}
				selectedStrategyText = strategiesList[strategySelect - 1];
			}
			else if (menuSelect == 2) {
				actveDoorsSelect++;
				if (actveDoorsSelect > (sizeof(activeDoorsList) / sizeof(activeDoorsList[0]))) {
					actveDoorsSelect = 1;
				}
				selectedDoorsText = activeDoorsList[actveDoorsSelect - 1];
			}
			else if (menuSelect == 3) {
				mapSelect++;
				if (mapSelect > (sizeof(mapList) / sizeof(mapList[0]))) {
					mapSelect = 1;
				}
				selectedMapText = mapList[mapSelect - 1];
			}
		}
		else if (key == GLUT_KEY_LEFT) {
			if (menuSelect == 1) {
				strategySelect--;
				if (strategySelect < 1) {
					strategySelect = (sizeof(strategiesList) / sizeof(strategiesList[0]));
				}
				selectedStrategyText = strategiesList[strategySelect - 1];
			}
			else if (menuSelect == 2) {
				actveDoorsSelect--;
				if (actveDoorsSelect < 1) {
					actveDoorsSelect = (sizeof(activeDoorsList) / sizeof(activeDoorsList[0]));
				}
				selectedDoorsText = activeDoorsList[actveDoorsSelect - 1];
			}
			else if (menuSelect == 3) {
				mapSelect--;
				if (mapSelect < 1) {
					mapSelect = (sizeof(mapList) / sizeof(mapList[0]));
				}
				selectedMapText = mapList[mapSelect - 1];
			}
		}
	}
}


void GraphicsEngine::reshape(int width, int height) {		// Resize the OpenGL window
	screenWidth = width; screenHeight = height;				// to ensure the mouse coordinates match 
															// we will use these values to set the coordinate system

	glViewport(0, 0, width, height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);							// Select The Projection Matrix
	glLoadIdentity();										// Reset The Projection Matrix
	aspect = (float)width / (float)height;
	gluOrtho2D((-100 - zoom) * aspect, (100 + zoom) * aspect, -100 - zoom, 100 + zoom);		//Adjusts aspect ratio

	glMatrixMode(GL_MODELVIEW);								// Select The Modelview Matrix
	glLoadIdentity();										// Reset The Modelview Matrix
}


void GraphicsEngine::runGraphicsEngine(int argc, char** argv) {
	glutInit(&argc, argv);								// Initialize GLUT
	glutInitWindowSize(screenWidth, screenHeight);						// Set the window's initial width & height
	glutInitWindowPosition(0, 0);						// Position the window's initial top-left corner
	window = glutCreateWindow("Aircraft Boarding Simulation");	// Create a window with the given title

	init();

	std::cout << "\nRunning the simulation..." << std::endl;
	glutDisplayFunc(display);							// Register display callback handler for window re-paint
	glutMainLoop();
}