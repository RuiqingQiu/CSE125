#include "stdafx.h"
#include "button.h"

button::button() {
	init();
}

button::button(string filename) {
	init();
	name = filename;
	setTexture(filename, btnState::NORMAL);
	setTexture(filename, btnState::SELECTED);
	setTexture(filename, btnState::PRESSED);
}

button::button(string filename, int x, int y) {
	init();
	name = filename;
	setTexture(filename, btnState::NORMAL);
	setPosition(x, y);
	setTexture(filename, btnState::SELECTED);
	setTexture(filename, btnState::PRESSED);
}

button::button(string filename, int x, int y, bool f) {
	init();
	name = filename;
	setTexture(filename, btnState::NORMAL);
	setPosition(x, y);
	setFixed(f, f);
	setTexture(filename, btnState::SELECTED);
	setTexture(filename, btnState::PRESSED);
}

button::button(string filename, int x, int y, bool xf, bool yf) {
	init();
	name = filename;
	setTexture(filename, btnState::NORMAL);
	setPosition(x, y);
	setFixed(xf, yf);
	texture[1] = texture[0];
}

button::button(string filename, int x, int y, int w, int h) {
	init();
	name = filename;
	setTexture(filename, btnState::NORMAL);
	setTexture(filename, btnState::SELECTED);
	setTexture(filename, btnState::PRESSED);
	setPosition(x, y);
	setSize(w, h);
}

button::button(string filename, int x, int y, int w, int h, bool f) {
	init();
	name = filename;
	setTexture(filename, btnState::NORMAL);
	setTexture(filename, btnState::SELECTED);
	setTexture(filename, btnState::PRESSED);
	setPosition(x, y);
	setSize(w, h);
	setFixed(f, f);
}

button::button(string filename, int x, int y, int w, int h, bool xf, bool yf) {
	init();
	name = filename;
	setTexture(filename, btnState::NORMAL);
	setTexture(filename, btnState::SELECTED);
	setTexture(filename, btnState::PRESSED);
	setPosition(x, y);
	setSize(w, h);
	setFixed(xf, yf);
}

button::~button()
{
}

void button::init() {
	name = "noname";
	setPosition(0, 0);
	//default button size
	setSize(100, 30);
	setFixed(false, true);
	sWidth = 0;
	sHeight = 0;
	currState = btnState::NORMAL;
	scaleX = false;
	scaleY = false;
	path = "uiItem/buttons/";
}

bool button::isSelected(int x, int y) {
	if (x >= xPos && x < (xPos + width)) {
		if (y >= yPos && y < (yPos + height)) {
			return true;
		}
	}
	return false;
}

void button::onHover(int x, int y) {
	if (isSelected(x, y)) {
		currState = btnState::SELECTED;
	}
	else {
		currState = btnState::NORMAL;
	}
}

void button::onClick(int state, int x, int y) {
	if (isSelected(x, y) && state == GLUT_DOWN) {
		currState = btnState::PRESSED;
	}
}