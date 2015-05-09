#include "stdafx.h"
#include "numDisplay.h"


numDisplay::numDisplay() : guiItem() {
	createNumbers();
}

numDisplay::numDisplay(string filename) : guiItem(filename) {
	createNumbers();
}

numDisplay::numDisplay(string filename, int x, int y) : guiItem(filename, x, y) {
	createNumbers();
}

numDisplay::numDisplay(string filename, int x, int y, bool f) : guiItem(filename, x, y, f) {
	createNumbers();
}

numDisplay::numDisplay(string filename, int x, int y, bool xf, bool yf) : guiItem(filename, x, y, xf, yf) {
	createNumbers();
}

numDisplay::numDisplay(string filename, int x, int y, int w, int h) : guiItem(filename, x, y, w, h) {
	createNumbers();
}

numDisplay::numDisplay(string filename, int x, int y, int w, int h, bool f) : guiItem(filename, x, y, w, h, f) {
	createNumbers();
}

numDisplay::numDisplay(string filename, int x, int y, int w, int h, bool xf, bool yf) : guiItem(filename, x, y, w, h, xf, yf) {
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
	num_digits = DEFAULT_NUM_DIGITS;
	off = (10.0 / 100.0) * height;
	nSize = height - (off*2.0);
	for (int i = 0; i < num_digits; i++) {
		digits.push_back(new numbers((xPos + width - off) - (nSize*(i + 1)), yPos + off, nSize, nSize, xfixed, yfixed));
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
	off = (10.0 / 100.0) * height;
	nSize = height - (off*2.0);
	//want to manually make sure it stays relative to time left box
	for (int i = 0; i < num_digits; i++) {
		digits[i]->setPosition((xPos + width - off) - (nSize*(i + 1)), yPos + off);
	}
}