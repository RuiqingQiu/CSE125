#pragma once

#include <string>
#include <GL/glut.h>


class gui
{
public:
	gui();
	~gui();

	void draw(int width, int height);

	void drawText(int x, int y, std::string text, float r, float g, float b, void * font);
};

