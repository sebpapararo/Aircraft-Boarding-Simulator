#include "GraphicsEngine.h"

GraphicsEngine GE;

//Main function: GLUT runs as a console application starting at main()
int main(int argc, char** argv) {
	std::cout << "Aircraft Boarding Simulation started..." << std::endl;
	GE.runGraphicsEngine(argc, argv);

	return 0;
}