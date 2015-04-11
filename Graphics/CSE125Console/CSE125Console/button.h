#pragma once

#include <GL/glut.h>

class button
{
public:
	button();
	~button();

	bool setTexture(char * filename);

	void draw();

	void onClick();

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

