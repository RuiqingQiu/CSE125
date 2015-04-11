#pragma once

#include <GL/glut.h>
#include "SOIL.h"

class button
{
public:
	button();
	button(char * filename);
	button(char * filename, int x, int y);
	button(char * filename, int x, int y, bool f);
	button(char * filename, int x, int y, int w, int h);
	button(char * filename, int x, int y, int w, int h, bool f);
	~button();

	bool setTexture(char * filename);

	void draw();
	void onClick();

	void setPosition(int x, int y);
	void setSize(int w, int h);
	void setFixed(bool f);
	bool isFixed();

	void translatePos(int x, int y);

private:

	//store the texture
	GLuint texture[1];

	//top left corner position of texture
	int xPos;
	int yPos;

	//size of the texture
	int width;
	int height;

	bool fixedPosition;
};

