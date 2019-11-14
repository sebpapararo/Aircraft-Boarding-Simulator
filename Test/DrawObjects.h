#pragma once
#include "windows.h"
#include "Image_Loading/nvImage.h"

class DrawObjects {
public:
	void loadObject(GLuint texture, float rotate, float xTranslation, float yTranslation, float x, float y, float texLength, float r, float g, float b);
	GLuint loadPNG(char* name);
};