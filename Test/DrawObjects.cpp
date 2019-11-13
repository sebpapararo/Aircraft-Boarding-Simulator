#include "DrawObjects.h"

void DrawObjects::loadObject(GLuint texture, float rotate, float xTranslation, float yTranslation, float x, float y, float texLength, float r, float g, float b)
{
	glPushMatrix();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glTranslatef(xTranslation, yTranslation, 0);
	glRotatef(rotate, 0, 0, 1);

	glEnable(GL_TEXTURE_2D);
	glColor3f(r, g, b);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex2f(-x, -y);			//Bottom-left
	glTexCoord2f(0.0, texLength); glVertex2f(-x, y);	//Top-left
	glTexCoord2f(1.0, texLength); glVertex2f(x, y);		//Top-right
	glTexCoord2f(1.0, 0.0); glVertex2f(x, -y);			//Bottom-right
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

GLuint DrawObjects::loadPNG(char* name) {	//Loads textures
											// Texture loading object
	nv::Image img;
	GLuint myTextureID;

	// Return true on success
	if (img.loadImageFromFile(name))
	{
		glGenTextures(1, &myTextureID);
		glBindTexture(GL_TEXTURE_2D, myTextureID);
		glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
		glTexImage2D(GL_TEXTURE_2D, 0, img.getInternalFormat(), img.getWidth(), img.getHeight(), 0, img.getFormat(), img.getType(), img.getLevel(0));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f);
	}
	else
		MessageBox(NULL, "Failed to load texture", "End of the world", MB_OK | MB_ICONINFORMATION);
	return myTextureID;
}