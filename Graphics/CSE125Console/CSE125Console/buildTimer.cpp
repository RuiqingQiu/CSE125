#include "stdafx.h"
#include "buildTimer.h"


buildTimer::buildTimer() : guiItem() {
	createNumbers();
}

buildTimer::buildTimer(string filename) : guiItem(filename) {
	createNumbers();
}

buildTimer::buildTimer(string filename, int x, int y) : 
guiItem(filename, x, y) {
	createNumbers();
}

buildTimer::buildTimer(string filename, int x, int y, bool f) : 
guiItem(filename, x, y, f) {
	createNumbers();
}

buildTimer::buildTimer(string filename, int x, int y, bool xf, bool yf) : 
guiItem(filename, x, y, xf, yf) {
	createNumbers();
}
buildTimer::buildTimer(string filename, int x, int y, int w, int h) : 
guiItem(filename, x, y, w, h) {
	createNumbers();
}

buildTimer::buildTimer(string filename, int x, int y, int w, int h, bool f) : 
guiItem(filename, x, y, w, h, f) {
	createNumbers();
}

buildTimer::buildTimer(string filename, int x, int y, int w, int h, bool xf, bool yf) :
guiItem(filename, x, y, w, h, xf, yf) {
	createNumbers();
}

buildTimer::~buildTimer() {
}

void buildTimer::createNumbers() {
	timeLeft = MAX_TIME;
	start = std::clock();
	double off = (10.0 / 100.0) * height;
	int nSize = height - (off*2.0);
	for (int i = 0; i < NUM_DIGITS; i++) {
		digits[i] = new numbers((xPos + width - off) - (nSize*(i+1)), yPos + off, nSize, nSize, xfixed, yfixed);
	}
}

void buildTimer::update() {
	timeLeft = MAX_TIME - ((std::clock() - start) / CLOCKS_PER_SEC);
	int idx = timeLeft;
	for (int i = 0; i < NUM_DIGITS; i++) {
		if (!(idx >= 0)) break;
		int digit = idx % 10;
		digits[i]->numIdx = digit;
		idx /= 10;
	}
}

void buildTimer::draw() {
	guiItem::draw();
	for (int i = 0; i < NUM_DIGITS; i++) {
		int idx = digits[i]->numIdx;
		digits[i]->draw();
		//digits[i]->draw(&nums[idx]);
	}
}

/*
void buildTimer::setScaling(bool xs, bool ys, int w, int h) {
	guiItem::setScaling(xs, ys, w, h);
	for (int i = 0; i < NUM_DIGITS; i++) {
		digits[i].setScaling(xs, ys, w, h);
	}
}
*/

void buildTimer::rePosition(int x, int y, int w, int h) {
	guiItem::rePosition(x, y, w, h);
	/*
	for (int i = 0; i < NUM_DIGITS; i++) {
		digits[i].rePosition(x, y, w, h);
	}
	*/
	double off = (10.0 / 100.0) * height;
	int nSize = height - (off*2.0);
	//want to manually make sure it stays relative to time left box
	for (int i = 0; i < NUM_DIGITS; i++) {
		digits[i]->setPosition((xPos + width - off) - (nSize*(i+1)), yPos + off);
	}
}