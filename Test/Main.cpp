#include "GraphicsEngine.h"

GraphicsEngine GE;

//Main function: GLUT runs as a console application starting at main()
int main(int argc, char** argv) {
	GE.runGraphicsEngine(argc, argv);

	return 0;
}