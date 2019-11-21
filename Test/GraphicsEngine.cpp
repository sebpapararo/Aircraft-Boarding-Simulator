#include "GraphicsEngine.h"

int window = 0;
bool isConsole = false;
bool isBoarded = false;

bool isStarted = false;
int menuSelect = 1;
int strategySelect = 1;
int mapSelect = 1;

std::string strategiesList[] = { "Back-to-Front", "Seat-by-Seat", "Random", "Row-by-Row" };
std::string mapList[] = { "AirbusA319", "Boeing737" };

std::string setStrategyText = "--> Set boarding strategy: ";
std::string setMapText = "Set aircraft map: ";
std::string selectedStrategyText = "Back-to-Front";
std::string selectedMapText = "AirbusA319";

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
float g_aislePosY;
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

void GraphicsEngine::initSettings(int strategy, int layout) {

	if (layout == 1) {
		g_selectedAircraft = AirbusA319();
	}
	else {
		g_selectedAircraft = Boeing737();
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

	if (strategy == 1) {
		g_SS.backToFront(g_currentAlgorithm, g_noOfRows, g_activeTemplate, g_activeDoorPos, g_activePassengers);
	}
	else if (strategy == 2) {
		g_SS.seatBySeat(g_currentAlgorithm, g_noOfRows, g_noOfColumns, g_aircraftName, g_activeTemplate, g_activeDoorPos, g_activePassengers);
	}
	else if (strategy == 3) {
		g_SS.randomSeat(g_currentAlgorithm, g_noOfRows, g_noOfColumns, g_aircraftName, g_activeTemplate, g_activeDoorPos, g_activePassengers);
	}
	else {
		g_SS.rowByRow(g_currentAlgorithm, g_noOfRows, g_activeTemplate, g_activeDoorPos, g_activePassengers);
	}
}


void GraphicsEngine::display() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	FPSLock(FPSCap);

	//Menu
	if (!isStarted) {
		infoDisplay("Please use the arrow keys to set simulation settings:", -150.0f, 20.0f);

		infoDisplay(setStrategyText + selectedStrategyText, -150.0f, 0.0f);
		infoDisplay(setMapText + selectedMapText, -150.0f, -10.0f);

		infoDisplay("Press 'ENTER' to start the simulation.", -150.0f, -30.0f);
	}
	//Simulation
	else {
		//Passenger navigation
		g_PE.updatePositions(g_activePassengers, g_activeSeatedPassengers, g_aislePosY);

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
				float tempRotation = g_activePassengers[i].getRotation();
				DO.loadObject(Passenger1, tempRotation, tempInitPos.x, tempInitPos.y, passengerHeight, passengerWidth, 1.0f, 1.0f, 1.0f, 1.0f);
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
			infoDisplay("Boarding strategy: " + g_currentAlgorithm, -150.0f, -70.0f);

			// Display the current template name to the window
			infoDisplay("Aircraft map: " + g_selectedAircraft.getTemplateName(), -150.0f, -75.0f);

			infoDisplay(runtimeResultText + std::to_string(totalRuntime), -150.0f, -80.0f);
		}

		if (g_activePassengers.empty() && !isBoarded) {
			isBoarded = true;
			std::cout << "Boarding strategy strategy: " + g_currentAlgorithm << std::endl;
			std::cout << "Aircraft map: " + g_selectedAircraft.getTemplateName() << std::endl;
			std::cout << runtimeResultText + std::to_string(totalRuntime) << std::endl;
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
			initSettings(strategySelect, mapSelect);
			startTime = glutGet(GLUT_ELAPSED_TIME);
		}
		else {
			isStarted = false;
		}
	}
	
}

void GraphicsEngine::processSpecialKeys(int key, int x, int y) {
	if (!isStarted) {
		if (key == GLUT_KEY_UP) {
			if (menuSelect == 2) {
				menuSelect--;
				setStrategyText = "--> Set boarding strategy: ";
				setMapText = "Set aircraft map: ";
			}
			else {
				menuSelect++;
				setStrategyText = "Set boarding strategy: ";
				setMapText = "->> Set aircraft map: ";
			}
		}
		else if (key == GLUT_KEY_DOWN) {
			if (menuSelect == 1) {
				menuSelect++;
				setStrategyText = "Set boarding strategy: ";
				setMapText = "--> Set aircraft map: ";
			}
			else {
				menuSelect--;
				setStrategyText = "--> Set boarding strategy: ";
				setMapText = "Set aircraft map: ";
			}
		}
		else if (key == GLUT_KEY_RIGHT) {
			if (menuSelect == 1) {
				strategySelect++;
				if (strategySelect > 4) {
					strategySelect = 1;
				}
				selectedStrategyText = strategiesList[strategySelect - 1];
			}
			else if (menuSelect == 2) {
				mapSelect++;
				if (mapSelect > 2) {
					mapSelect = 1;
				}
				selectedMapText = mapList[mapSelect - 1];
			}
		}
		else if (key == GLUT_KEY_LEFT) {
			if (menuSelect == 1) {
				strategySelect--;
				if (strategySelect < 1) {
					strategySelect = 4;
				}
				selectedStrategyText = strategiesList[strategySelect - 1];
			}
			else if (menuSelect == 2) {
				mapSelect--;
				if (mapSelect < 1) {
					mapSelect = 2;
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
	gluOrtho2D(-100 * aspect, 100 * aspect, -100, 100);		//Adjusts aspect ratio

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