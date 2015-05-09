#include "stdafx.h"
#include "buildTimer.h"

string buildTimer::textPath = "text/time.jpg";

buildTimer::buildTimer() : numDisplay() {
	init();
}

buildTimer::buildTimer(int x, int y) : 
numDisplay(textPath, x, y) {
	init();
}

buildTimer::buildTimer(int x, int y, bool f) : 
numDisplay(textPath, x, y, f) {
	init();
}

buildTimer::buildTimer(int x, int y, bool xf, bool yf) : 
numDisplay(textPath, x, y, xf, yf) {
	init();
}
buildTimer::buildTimer(int x, int y, int w, int h) : 
numDisplay(textPath, x, y, w, h) {
	init();
}

buildTimer::buildTimer(int x, int y, int w, int h, bool f) : 
numDisplay(textPath, x, y, w, h, f) {
	init();
}

buildTimer::buildTimer(int x, int y, int w, int h, bool xf, bool yf) :
numDisplay(textPath, x, y, w, h, xf, yf) {
	init();
}

buildTimer::~buildTimer() {
}

void buildTimer::init() {
	timeLeft = BUILD_MAX_TIME;
	start = std::clock();
}

void buildTimer::update() {
	timeLeft = BUILD_MAX_TIME - ((std::clock() - start) / CLOCKS_PER_SEC);
	displayValue = timeLeft;
	numDisplay::update();
}