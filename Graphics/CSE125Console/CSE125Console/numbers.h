#pragma once
#include "guiItem.h"

//global static variables to load numbers only once
static bool nums_set = false;
static GLuint nums[10];

class numbers : public guiItem
{
public:
	numbers();
	numbers(int x, int y);
	numbers(int x, int y, bool f);
	numbers(int x, int y, bool xf, bool yf);
	numbers(int x, int y, int w, int h);
	numbers(int x, int y, int w, int h, bool f);
	numbers(int x, int y, int w, int h, bool xf, bool yf);
	~numbers();

	void init();
	void draw();
	void draw(GLuint * t);
	bool setTexture(int i);
	bool setAllNumbers();

	int numIdx;
};

