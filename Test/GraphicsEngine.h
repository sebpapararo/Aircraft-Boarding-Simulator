#pragma once
#include <windows.h>  // for MS Windows

#include "DrawObjects.h"
#include "Aircraft.h"
#include "Passenger.h"
#include "PhysicsEngine.h"
#include "SeatingStrategies.h"

#include <string>
#include <fstream>
#include <iostream>

class GraphicsEngine {
public:
	void runGraphicsEngine(int argc, char** argv);

private:
	static void init();
	static void initSettings(int strategy, int layout);
	static void display();
	static void FPSLock(int FPSCap);
	static void infoDisplay(std::string outputString, float posX, float posY);
	static void processKeys(unsigned char key, int x, int y);
	static void processSpecialKeys(int key, int x, int y);
	static void reshape(int width, int height);

};