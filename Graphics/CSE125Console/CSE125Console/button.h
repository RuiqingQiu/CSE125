#pragma once

#include <GL/glut.h>

class button
{
public:
	button();
	button(char * filename);
	button(char * filename, int x, int y);
	~button();

	bool setTexture(char * filename);

	void draw();
	void onClick();

	void setPosition(int x, int y);

private:

	//store the texture
	GLuint texture[1];

	//top left corner position of texture
	int xPos;
	int yPos;

	//size of the texture
	int width;
	int height;
};

