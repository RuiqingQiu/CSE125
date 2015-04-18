#pragma once
#include <iostream>
#include <string>
#include <GL/glut.h>
#include "SOIL.h"

using namespace std;

enum class btnState {
	NORMAL,
	SELECTED,
	PRESSED
};

class guiItem
{
public:
	//constructors
	guiItem();
	guiItem(string filename);
	guiItem(string filename, int x, int y);
	guiItem(string filename, int x, int y, bool f);
	guiItem(string filename, int x, int y, bool xf, bool yf);
	guiItem(string filename, int x, int y, int w, int h);
	guiItem(string filename, int x, int y, int w, int h, bool f);
	guiItem(string filename, int x, int y, int w, int h, bool xf, bool yf);
	~guiItem();

	virtual void init();
	
	//setters
	bool setTexture(string filename, btnState state);
	void setPosition(int x, int y);
	void setSize(int w, int h);
	void setFixed(bool x, bool y);
	virtual void setScaling(bool xs, bool ys, int w, int h);

	//getters
	bool xisFixed();
	bool yisFixed();

	//update
	virtual void update();

	//drawing functions
	virtual void draw();
	void translate(int x, int y);
	virtual void rePosition(int x, int y, int w, int h);

protected:
	string path;
	//store the texture, only 0 is used in gui, 1 and 2 are for button sub-class
	// [0] is main texture
	// [1] is hovered texture
	// [2] is clicked texture
	GLuint texture[3];

	//top left corner position of texture
	int xPos;
	int yPos;

	//size of the texture
	int width;
	int height;
	
	//fixed position on screen
	bool xfixed;
	bool yfixed;

	//for scale (if scaling) instead of translating on resize
	bool scaleX;
	bool scaleY;
	int sWidth;
	int sHeight;

	//for selecting which texture
	btnState currState;
};

