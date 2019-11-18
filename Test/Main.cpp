#include "GraphicsEngine.h"
#include <thread>


GraphicsEngine GE;

//Main function: GLUT runs as a console application starting at main()
int main(int argc, char** argv) {
	std::cout << "Aircraft Boarding Simulation started..." << std::endl;
	// GE.runGraphicsEngine(argc, argv);

	std::thread t1(&GraphicsEngine::runGraphicsEngine, argc, argv);
	t1.join();

	
	return 0;
}