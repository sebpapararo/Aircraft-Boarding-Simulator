#include "GraphicsEngine.h"

int screenWidth = GetSystemMetrics(SM_CXSCREEN), screenHeight = GetSystemMetrics(SM_CYSCREEN);
float aspect;
bool keys[256];

//FPS and runtime timing
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

// Select which aircraft you want to run the simulation
// Choose from: 'AirbusA319' | 'Boeing737'
Aircraft selectedAircraft = AirbusA319();
//Aircraft selectedAircraft = Boeing737();
std::string aircraftName = selectedAircraft.getTemplateName();

vector<vector<vec2>> activeTemplate = selectedAircraft.getTemplate();
vector<vector<vec2>> activeDoorPos = selectedAircraft.getDoorPos();
int noOfRows = selectedAircraft.getNoOfRows();			// This used to be 'templatei'
int noOfColumns = selectedAircraft.getNoOfColumns();	// This used to be 'templatej'
vector<Passenger> activePassengers;
vector<Passenger> activeSeatedPassengers;
float aislePosY = selectedAircraft.getAislePosY();
vector<vec2> activeWallPos = selectedAircraft.getWallPos();
std::string currentAlgorithm;

PhysicsEngine PE;
SeatingStrategies SS;


void GraphicsEngine::init() {
	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
	glutKeyboardFunc(processKeys);
	//glutSpecialFunc();

	reshape(screenWidth, screenHeight);

	Passenger1 = DO.loadPNG(passenger1Path);

	//SS.backToFront(currentAlgorithm, noOfRows, activeTemplate, activeDoorPos, activePassengers);
	//SS.seatBySeat(currentAlgorithm, noOfRows, noOfColumns, aircraftName, activeTemplate, activeDoorPos, activePassengers);
	//SS.randomSeat(currentAlgorithm, noOfRows, noOfColumns, aircraftName, activeTemplate, activeDoorPos, activePassengers);
	SS.rowByRow(currentAlgorithm, noOfRows, activeTemplate, activeDoorPos, activePassengers);

	startTime = glutGet(GLUT_ELAPSED_TIME);
}


void GraphicsEngine::display() {
	deltaTime();	//Temporary: render at 60 frames per second AND do movement based on time (not frames) using delta time in physics engine.

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	//Draws seats
	for (int i = 0; i < noOfRows; i++) {
		for (size_t j = 0; j < activeTemplate[i].size(); j++) {
			DO.loadObject(Seat1, 90.0f, activeTemplate[i][j].x, activeTemplate[i][j].y, seatHeight, seatWidth, 1.0f, 0.2f, 0.8f, 0.2f);
		}
	}

	//Draws walls as lines
	glColor3f(0.5f, 0.5f, 0.5f);
	glLineWidth(5.0f);
	glBegin(GL_LINES);
	for (size_t i = 0; i < activeWallPos.size() - 1; i += 2) {
		glVertex2f(activeWallPos[i].x, activeWallPos[i].y);
		glVertex2f(activeWallPos[i + 1].x, activeWallPos[i + 1].y);
	}
	glEnd();


	//Collision detection/passenger navigation
	PE.updatePositions(activePassengers, activeSeatedPassengers, aislePosY);

	//Draws seeking passengers
	for (size_t i = 0; i < activePassengers.size(); i++) {
		vec2 tempInitPos = activePassengers[i].getInitPos();
		float tempRotation = activePassengers[i].getRotation();
		DO.loadObject(Passenger1, tempRotation, tempInitPos.x, tempInitPos.y, passengerHeight, passengerWidth, 1.0f, 1.0f, 1.0f, 1.0f);
	}

	//Draws seated passengerss
	for (size_t i = 0; i < activeSeatedPassengers.size(); i++) {
		vec2 tempInitPos = activeSeatedPassengers[i].getInitPos();
		DO.loadObject(Passenger1, 90.0f, tempInitPos.x, tempInitPos.y, passengerHeight, passengerWidth, 1.0f, 1.0f, 1.0f, 1.0f);
	}

	//Runtime timing
	if (!activePassengers.empty()) {
		double endTime = glutGet(GLUT_ELAPSED_TIME);
		totalRuntime = (endTime - startTime) / 1000;
	}
	infoDisplay(runtimeResultText + std::to_string(totalRuntime), -150.0f, -80.0f);

	// Display the current template name to the window
	infoDisplay("Current plane template: " + selectedAircraft.getTemplateName(), -150.0f, -75.0f);

	// Display the current algorithm to the window
	infoDisplay("Current algorithm: " + currentAlgorithm, -150.0f, -70.0f);

	glFlush();	//Render now
	glutSwapBuffers();

	glutPostRedisplay();
}


//Locks frame rate to FRAMES_PER_SECOND
void GraphicsEngine::deltaTime() {
	const int FRAMES_PER_SECOND = 60;
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
	glutCreateWindow("Aircraft Boarding Simulation");	// Create a window with the given title

	init();

	glutDisplayFunc(display);							// Register display callback handler for window re-paint
	glutMainLoop();
}