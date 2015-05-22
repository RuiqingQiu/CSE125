#include "stdafx.h"
#include "numDisplay.h"


numDisplay::numDisplay() : guiItem() {
	createNumbers();
}

numDisplay::numDisplay(string filename) : guiItem(filename) {
	mainmenuLoading = 0;
	createNumbers();
}

numDisplay::numDisplay(string filename, int x, int y) : guiItem(filename, x, y) {
	mainmenuLoading = 0;
	createNumbers();
}

numDisplay::numDisplay(string filename, int x, int y, bool f) : guiItem(filename, x, y, f) {
	mainmenuLoading = 0;
	createNumbers();
}

numDisplay::numDisplay(string filename, int x, int y, bool xf, bool yf) : guiItem(filename, x, y, xf, yf) {
	mainmenuLoading = 0;
	createNumbers();
}

numDisplay::numDisplay(string filename, int x, int y, int w, int h) : guiItem(filename, x, y, w, h) {
	mainmenuLoading = 0;
	createNumbers();
}

numDisplay::numDisplay(string filename, int x, int y, int w, int h, int loading) : guiItem(filename, x, y, w, h) {
	mainmenuLoading = loading; // constructor for the loading number display
	createNumbers();
}

numDisplay::numDisplay(string filename, int x, int y, int w, int h, bool f) : guiItem(filename, x, y, w, h, f) {
	mainmenuLoading = 0;
	createNumbers();
}

numDisplay::numDisplay(string filename, int x, int y, int w, int h, bool xf, bool yf) : guiItem(filename, x, y, w, h, xf, yf) {
	mainmenuLoading = 0;
	createNumbers();
}

numDisplay::~numDisplay() {
	for (int i = 0; i < digits.size(); i++) {
		delete digits[i];
	}
	digits.clear();
}

void numDisplay::createNumbers() {
	displayValue = 0;
	if (!mainmenuLoading){
		num_digits = DEFAULT_NUM_DIGITS; // 2
	}
	else{
		num_digits = DEFAULT_NUM_DIGITS_FOR_MAINMENU; // 1
	}
	off = (20.0 / 100.0) * height;
	nSize = height - (off*2.0);
	for (int i = 0; i < num_digits; i++) {
		if (!mainmenuLoading){
			digits.push_back(new numbers((xPos + width - (off*3.0)) - (nSize*(i + 1)), yPos + off, nSize, nSize, xfixed, yfixed));
		}
		else{
			off = (24.0/ 100.0) * height;
			nSize = height - (off*2) -2;
			digits.push_back(new numbers((xPos +  (nSize*(i+0.8))), yPos + off + 1, nSize, nSize, xfixed, yfixed)); // for mainmenu display
		}
	}
}

void numDisplay::update() {
	int idx = displayValue;
	for (int i = 0; i < num_digits; i++) {
		if (!(idx >= 0)) break;
		int digit = idx % 10;
		digits[i]->numIdx = digit;
		idx /= 10;
	}
}

void numDisplay::draw() {
	guiItem::draw();
	for (int i = 0; i < digits.size(); i++) {
		digits[i]->draw();
	}
}

void numDisplay::rePosition(int x, int y, int w, int h) {
	guiItem::rePosition(x, y, w, h);
	off = (20.0 / 100.0) * height;
	nSize = height - (off*2.0);
	//want to manually make sure it stays relative to time left box
	for (int i = 0; i < num_digits; i++) {
		digits[i]->setPosition((xPos + width - (off*3.0)) - (nSize*(i + 1)), yPos + off);
	}
}