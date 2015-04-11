#pragma once

#include <iostream>
#include <GL/glut.h>
#include "SOIL.h"

class button
{
public:
	button();
	button(char * filename);
	button(char * filename, int x, int y);
	button(char * filename, int x, int y, bool xf, bool yf);
	button(char * filename, int x, int y, int w, int h);
	button(char * filename, int x, int y, int w, int h, bool xf, bool yf);
	~button();

	bool setTexture(char * filename);

	void draw();
	void onClick();

	void setPosition(int x, int y);
	void setSize(int w, int h);
	void setFixed(bool x, bool y);

	bool xisFixed();
	bool yisFixed();

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

	bool xfixed;
	bool yfixed;
};

