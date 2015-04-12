#include "stdafx.h"
#include "guiItem.h"

guiItem::guiItem() {
	xPos = 0;
	yPos = 0;
	xfixed = false;
	yfixed = true;
	scaleX = false;
	scaleY = false;
	sWidth = 0;
	sHeight = 0;
}

guiItem::guiItem(char * filename) {
	xPos = 0;
	yPos = 0;
	setTexture(filename);
	xfixed = false;
	yfixed = true;
	scaleX = false;
	scaleY = false;
	sWidth = 0;
	sHeight = 0;
}

guiItem::guiItem(char * filename, int x, int y) {
	setTexture(filename);
	setPosition(x, y);
	xfixed = false;
	yfixed = true;
	scaleX = false;
	scaleY = false;
	sWidth = 0;
	sHeight = 0;
}

guiItem::guiItem(char * filename, int x, int y, bool f) {
	setTexture(filename);
	setPosition(x, y);
	xfixed = f;
	yfixed = f;
	scaleX = false;
	scaleY = false;
	sWidth = 0;
	sHeight = 0;
}

guiItem::guiItem(char * filename, int x, int y, bool xf, bool yf) {
	setTexture(filename);
	setPosition(x, y);
	xfixed = xf;
	yfixed = yf;
	scaleX = false;
	scaleY = false;
	sWidth = 0;
	sHeight = 0;
}

guiItem::guiItem(char * filename, int x, int y, int w, int h) {
	setTexture(filename);
	setPosition(x, y);
	setSize(w, h);
	xfixed = false;
	yfixed = true;
	scaleX = false;
	scaleY = false;
	sWidth = 0;
	sHeight = 0;
}

guiItem::guiItem(char * filename, int x, int y, int w, int h, bool f) {
	setTexture(filename);
	setPosition(x, y);
	setSize(w, h);
	xfixed = f;
	yfixed = f;
	scaleX = false;
	scaleY = false;
	sWidth = 0;
	sHeight = 0;
}

guiItem::guiItem(char * filename, int x, int y, int w, int h, bool xf, bool yf) {
	setTexture(filename);
	setPosition(x, y);
	setSize(w, h);
	xfixed = xf;
	yfixed = yf;
	scaleX = false;
	scaleY = false;
	sWidth = 0;
	sHeight = 0;
}

guiItem::~guiItem()
{
}

void guiItem::setSize(int x, int y) {
	width = x;
	height = y;
}
bool guiItem::setTexture(char * filename) {
	texture[0] = SOIL_load_OGL_texture
		(
		filename
		,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	if (texture[0] == 0)
	{
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
		return false;
	}
	else{
		printf("SOIL loading success\n");
	}

	//get the size of the texture
	
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);
	//return true if successfully set texture
	//std::cout << filename << std::endl;
	//std::cout << "width: " << width << std::endl;
	//std::cout << "height: " << height << std::endl;
	return false;
}

void guiItem::draw() {
	//bind the texture and draw it

	glDisable(GL_LIGHTING);
	glPushMatrix();
	//glLoadMatrixd(glmatrix.getPointer());

	glEnable(GL_TEXTURE_2D);
	//glActiveTexture(GL_TEXTURE1);

	glBindTexture(GL_TEXTURE_2D, texture[0]);
	// Make sure no bytes are padded:
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Draw a textured quad
	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(xPos, yPos, 0);
	glTexCoord2f(0, 1); glVertex3f(xPos, yPos + height, 0);
	glTexCoord2f(1, 1); glVertex3f(xPos + width, yPos + height, 0);
	glTexCoord2f(1, 0); glVertex3f(xPos + width, yPos, 0);
	glEnd();

	glPopMatrix();
	//glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

}

void guiItem::setPosition(int x, int y) {
	xPos = x;
	yPos = y;
}

void guiItem::rePosition(int x, int y, int w, int h) {
	//scaling mode for x
	if (scaleX) {
		double curr = double(xPos) / sWidth;
		xPos = curr * w;
		sWidth = w;
	}
	//translate mode for x
	else if (!xfixed) {
		xPos += x;
	}
	//scaling mode for y
	if (scaleY) {
		double curr = double(yPos) / sHeight;
		yPos = curr * h;
		sHeight = h;
	}
	//translate mode for y
	else if (!yfixed) {
		yPos += y;
	}
}

void guiItem::setFixed(bool x, bool y) {
	xfixed = x;
	yfixed = y;
}

bool guiItem::xisFixed() {
	return xfixed;
}

bool guiItem::yisFixed() {
	return yfixed;
}

void guiItem::setScaling(bool xs, bool ys, int w, int h) {
	scaleX = xs;
	scaleY = ys;
	sWidth = w;
	sHeight = h;
}