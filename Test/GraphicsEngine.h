#pragma once
#include <windows.h>  // for MS Windows

#include "DrawObjects.h"
#include "Aircraft.h"
#include "Passenger.h"
#include "PhysicsEngine.h"
#include "SeatingStrategies.h"

#include <GL\GL.h>			// Header File For The OpenGL32 Library
#include <GL\GLU.h>			// Header File For The GLu32 Library
#include <glut/glut.h>		// GLUT, includes glu.h and gl.h

#include <string>
#include <fstream>

// #include <iostream>

// #include "GLFW/glfw3.h"

class GraphicsEngine {
public:
	void runGraphicsEngine(int argc, char** argv);

private:
	static void init();
	static void display();
	static void FPSLock();
	//static void displayFPS();
	static void infoDisplay(std::string outputString, float posX, float posY);
	static void processKeys(unsigned char key, int x, int y);
	static void reshape(int width, int height);

};