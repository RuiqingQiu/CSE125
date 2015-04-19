#pragma once
#include "guiItem.h"

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

	int numIdx;
	GLuint nums[10];
};

