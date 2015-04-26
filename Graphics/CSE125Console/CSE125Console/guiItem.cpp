#include "stdafx.h"
#include "guiItem.h"

guiItem::guiItem() {
	init();
}

guiItem::guiItem(string filename) {
	init();
	setTexture(filename, btnState::NORMAL);
	setTexture(filename, btnState::SELECTED);
	setTexture(filename, btnState::PRESSED);
}

guiItem::guiItem(string filename, int x, int y) {
	init();
	setTexture(filename, btnState::NORMAL);
	setPosition(x, y);
	setTexture(filename, btnState::SELECTED);
	setTexture(filename, btnState::PRESSED);
}

guiItem::guiItem(string filename, int x, int y, bool f) {
	init();
	setTexture(filename, btnState::NORMAL);
	setPosition(x, y);
	setFixed(f, f);
	setTexture(filename, btnState::SELECTED);
	setTexture(filename, btnState::PRESSED);
}

guiItem::guiItem(string filename, int x, int y, bool xf, bool yf) {
	init();
	setTexture(filename, btnState::NORMAL);
	setPosition(x, y);
	setFixed(xf, yf);
	setTexture(filename, btnState::SELECTED);
	setTexture(filename, btnState::PRESSED);
}

guiItem::guiItem(string filename, int x, int y, int w, int h) {
	init();
	setTexture(filename, btnState::NORMAL);
	setPosition(x, y);
	setSize(w, h);
	setTexture(filename, btnState::SELECTED);
	setTexture(filename, btnState::PRESSED);
}

guiItem::guiItem(string filename, int x, int y, int w, int h, bool f) {
	init();
	setTexture(filename, btnState::NORMAL);
	setPosition(x, y);
	setSize(w, h);
	setFixed(f, f);
	setTexture(filename, btnState::SELECTED);
	setTexture(filename, btnState::PRESSED);
}

guiItem::guiItem(string filename, int x, int y, int w, int h, bool xf, bool yf) {
	init();
	setTexture(filename, btnState::NORMAL);
	setPosition(x, y);
	setSize(w, h);
	setFixed(xf, yf);
	setTexture(filename, btnState::SELECTED);
	setTexture(filename, btnState::PRESSED);
}

void guiItem::init() {
	setPosition(0, 0);
	setSize(100, 100);
	setFixed(false, true);
	sWidth = 0;
	sHeight = 0;
	currState = btnState::NORMAL;
	scaleX = false;
	scaleY = false;
	path = "uiItem/";
}

guiItem::~guiItem()
{
}

void guiItem::setSize(int x, int y) {
	width = x;
	height = y;
}

bool guiItem::setTexture(string filename, btnState state) {
	GLuint * t;
	string concat = path + filename;
	if (state == btnState::PRESSED) {
		t = &texture[2];
	}
	else if (state == btnState::SELECTED) {
		t = &texture[1];
	}
	else {
		t = &texture[0];
	}
	*t = SOIL_load_OGL_texture
		(
		concat.c_str()
		,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	if (*t == 0)
	{
		std::cout << concat.c_str() << std::endl;
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
		return false;
	}

	//return true if successfully set texture
	//std::cout << filename << std::endl;
	//std::cout << "width: " << width << std::endl;
	//std::cout << "height: " << height << std::endl;
	return true;
}

void guiItem::update() {
	//do nothing as default
}

void guiItem::draw() {
	//bind the texture and draw it

	glDisable(GL_LIGHTING);
	glPushMatrix();
	//glLoadMatrixd(glmatrix.getPointer());

	glEnable(GL_TEXTURE_2D);
	//glActiveTexture(GL_TEXTURE1);

	if (currState == btnState::PRESSED) {
		glBindTexture(GL_TEXTURE_2D, texture[2]);
	}
	else if (currState == btnState::SELECTED) {
		glBindTexture(GL_TEXTURE_2D, texture[1]);
	}
	else {
		glBindTexture(GL_TEXTURE_2D, texture[0]);
	}
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

void guiItem::translate(int x, int y) {
	xPos += x;
	yPos += y;
}