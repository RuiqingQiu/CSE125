#pragma once
#include <iostream>
#include <GL/glut.h>
#include "SOIL.h"

using namespace std;

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
	bool setTexture(string filename, bool select);
	void setPosition(int x, int y);
	void setSize(int w, int h);
	void setFixed(bool x, bool y);
	void setScaling(bool xs, bool ys, int w, int h);

	//getters
	bool xisFixed();
	bool yisFixed();

	//drawing functions
	virtual void draw();
	void translate(int x, int y);
	virtual void rePosition(int x, int y, int w, int h);

protected:
	string path;
	//store the texture
	// [0] is main texture
	// [1] is clicked/hovered texture
	GLuint texture[2];

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
	bool selected;
};

