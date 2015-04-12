#include "stdafx.h"
#include "button.h"

/*
 * things to implement:
 * button::isClicked() 
 *		check if mouseclick coordinates are inside button coordinates
 * button::onClick()
 *		game logic: on click action
 */

button::button() : guiItem() {
	name = "noname";
}

button::button(char * filename) : 
guiItem(filename) {
	name = filename;
}

button::button(char * filename, int x, int y) : 
guiItem(filename, x, y) {
	name = filename;
}

button::button(char * filename, int x, int y, bool f) :
guiItem(filename, x, y, f) {
	name = filename;
}

button::button(char * filename, int x, int y, bool xf, bool yf) : 
guiItem(filename, x, y, xf, yf) {
	name = filename;
}

button::button(char * filename, int x, int y, int w, int h) :
guiItem(filename, x, y, w, h) {
	name = filename;
}

button::button(char * filename, int x, int y, int w, int h, bool f) :
guiItem(filename, x, y, w, h, f) {
	name = filename;
}

button::button(char * filename, int x, int y, int w, int h, bool xf, bool yf) :
guiItem(filename, x, y, w, h, xf, yf) {
	name = filename;
}

button::~button()
{
}


bool button::isClicked(int x, int y) {
	if (x >= xPos && x < (xPos + width)) {
		if (y >= yPos && y < (yPos + height)) {
			return true;
		}
	}
	return false;
}

void button::onClick(int x, int y) {
	if (isClicked(x, y)) {
		//game logic here
		std::cout << name << " was clicked!" << std::endl;
	}
}