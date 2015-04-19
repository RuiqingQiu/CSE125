#include "stdafx.h"
#include "background.h"


background::background()
{
}

background::background(string filename) {
	init();
	setTexture(filename, btnState::NORMAL);
	setTexture(filename, btnState::SELECTED);
	setTexture(filename, btnState::PRESSED);
}

background::background(string filename, int w, int h) {
	init();
	setSize(w, h);
	setTexture(filename, btnState::NORMAL);
	setTexture(filename, btnState::SELECTED);
	setTexture(filename, btnState::PRESSED);
}

void background::rePosition(int x, int y, int w, int h) {
	setSize(w, h);
}

background::~background()
{
}

void background::init() {
	setPosition(0, 0);
	setSize(100, 100);
	setFixed(false, true);
	sWidth = 0;
	sHeight = 0;
	currState = btnState::NORMAL;
	scaleX = false;
	scaleY = false;
	path = "uiItem/images/";
}
