#include "stdafx.h"
#include "button.h"

button::button() {
	init();
}

button::button(string filename) {
	init();
	name = filename;
	setTexture(filename, false);
	texture[1] = texture[0];
}

button::button(string filename, int x, int y) {
	init();
	name = filename;
	setTexture(filename, false);
	setPosition(x, y);
	texture[1] = texture[0];
}

button::button(string filename, int x, int y, bool f) {
	init();
	name = filename;
	setTexture(filename, false);
	setPosition(x, y);
	setFixed(f, f);
	texture[1] = texture[0];
}

button::button(string filename, int x, int y, bool xf, bool yf) {
	init();
	name = filename;
	setTexture(filename, false);
	setPosition(x, y);
	setFixed(xf, yf);
	texture[1] = texture[0];
}

button::button(string filename, int x, int y, int w, int h) {
	init();
	name = filename;
	setTexture(filename, false);
	setPosition(x, y);
	setSize(w, h);
	texture[1] = texture[0];
}

button::button(string filename, int x, int y, int w, int h, bool f) {
	init();
	name = filename;
	setTexture(filename, false);
	setPosition(x, y);
	setSize(w, h);
	setFixed(f, f);
	texture[1] = texture[0];
}

button::button(string filename, int x, int y, int w, int h, bool xf, bool yf) {
	init();
	name = filename;
	setTexture(filename, false);
	setPosition(x, y);
	setSize(w, h);
	setFixed(xf, yf);
	texture[1] = texture[0];
}

button::~button()
{
}

void button::init() {
	name = "noname";
	setPosition(0, 0);
	setSize(100, 100);
	setFixed(false, true);
	sWidth = 0;
	sHeight = 0;
	selected = false;
	scaleX = false;
	scaleY = false;
	path = "uiItem/buttons/";
}

bool button::isClicked(int x, int y) {
	if (x >= xPos && x < (xPos + width)) {
		if (y >= yPos && y < (yPos + height)) {
			return true;
		}
	}
	return false;
}

void button::onClick(int state, int x, int y) {
	std::cout << "x: " << x << std::endl;
	std::cout << "y: " << y << std::endl;

	if (isClicked(x, y)) {
		if (state == GLUT_DOWN) {
			selected = true;
		}
		if (state == GLUT_UP) {
			selected = false;
		}
		std::cout << name.c_str() << " was clicked!" << std::endl;
	}
}