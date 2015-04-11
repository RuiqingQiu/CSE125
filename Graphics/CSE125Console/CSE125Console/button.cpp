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
}

button::button(char * filename) : 
guiItem(filename) {
}

button::button(char * filename, int x, int y) : 
guiItem(filename, x, y) {
}

button::button(char * filename, int x, int y, bool f) :
guiItem(filename, x, y, f) {
}

button::button(char * filename, int x, int y, bool xf, bool yf) : 
guiItem(filename, x, y, xf, yf) {
}

button::button(char * filename, int x, int y, int w, int h) :
guiItem(filename, x, y, w, h) {
}

button::button(char * filename, int x, int y, int w, int h, bool f) :
guiItem(filename, x, y, w, h, f) {
}

button::button(char * filename, int x, int y, int w, int h, bool xf, bool yf) :
guiItem(filename, x, y, w, h, xf, yf) {
}

button::~button()
{
}


bool button::isClicked() {
	return false;
}

void button::onClick() {
	//do somethin
}