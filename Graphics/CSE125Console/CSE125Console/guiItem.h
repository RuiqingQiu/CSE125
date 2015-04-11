#pragma once
#include <iostream>
#include <GL/glut.h>
#include "SOIL.h"

class guiItem
{
public:
	guiItem();
	guiItem(char * filename);
	guiItem(char * filename, int x, int y);
	guiItem(char * filename, int x, int y, bool f);
	guiItem(char * filename, int x, int y, bool xf, bool yf);
	guiItem(char * filename, int x, int y, int w, int h);
	guiItem(char * filename, int x, int y, int w, int h, bool f);
	guiItem(char * filename, int x, int y, int w, int h, bool xf, bool yf);
	~guiItem();

	bool setTexture(char * filename);

	virtual void draw();

	void setPosition(int x, int y);
	void setSize(int w, int h);
	void setFixed(bool x, bool y);

	bool xisFixed();
	bool yisFixed();

	virtual void translatePos(int x, int y);

protected:
	//store the texture
	// [0] is main texture
	// [1] is clicked/hovered texture? (not implemented yet)
	GLuint texture[2];

	//top left corner position of texture
	int xPos;
	int yPos;

	//size of the texture
	int width;
	int height;

	bool xfixed;
	bool yfixed;
};

