#include "stdafx.h"
#include "battletimer.h"


string battleTimer::textPath = "text/time_long.png";
battleTimer::battleTimer() : numDisplay() {
	createNumbers();
}

battleTimer::battleTimer(int x, int y) :
numDisplay(textPath, x, y) {
	createNumbers();
}

battleTimer::battleTimer(int x, int y, bool f) :
numDisplay(textPath, x, y, f) {
	createNumbers();
}

battleTimer::battleTimer(int x, int y, bool xf, bool yf) :
numDisplay(textPath, x, y, xf, yf) {
	createNumbers();
}
battleTimer::battleTimer(int x, int y, int w, int h) :
numDisplay(textPath, x, y, w, h) {
	createNumbers();
}

battleTimer::battleTimer(int x, int y, int w, int h, bool f) :
numDisplay(textPath, x, y, w, h, f) {
	createNumbers();;
}

battleTimer::battleTimer(int x, int y, int w, int h, bool xf, bool yf) :
numDisplay(textPath, x, y, w, h, xf, yf) {
	createNumbers();
}

battleTimer::~battleTimer() {
}

void battleTimer::createNumbers() {
	secLeft = 0;
	minLeft = MIN;
	//start = std::clock();

	int off_comma = (off*3.0) + nSize;
	for (int i = num_digits; i < BATTLE_NUM_DIGITS; i++) {
		digits.push_back(new numbers((xPos + width - off_comma) - (nSize*(i + 1)), yPos + off, nSize, nSize, xfixed, yfixed));
	}

	colon = new guiItem("text/symbols/colon.jpg", (xPos + width - (off*3.0)) - (nSize * 3), yPos + off, nSize, nSize); // all things have the same size 
}

void battleTimer::update(){
	// convert the time used to second
	//int timeUsed = (std::clock() - start) / CLOCKS_PER_SEC;
	// mod gives the reminder
	//int sec = timeUsed % BATTLE_MAX_TIME; // sec used
	//int min = (timeUsed - sec) / BATTLE_MAX_TIME;// mins used

	// if minLeft is less then 0, don't update anymore
	if (minLeft <= -1){
		secLeft = 0;
		//return;
	}
	// if still time left 
	else{
		//minLeft = MIN - min; // calcualte the min left
		//secLeft = BATTLE_MAX_TIME - sec;
	}
	
	// update sec first
	displayValue = secLeft;
	numDisplay::update();

	// then update minutes
	int idx = minLeft;
	std::cout << minLeft << std::endl;
	for (int i = num_digits; i < BATTLE_NUM_DIGITS; i++) {
		if (!(idx >= 0)) break;
		int digit = idx % 10;
		digits[i]->numIdx = digit;
		idx /= 10;
	}
}


void battleTimer::draw(){
	numDisplay::draw();
	colon->draw();
}


void battleTimer::rePosition(int x, int y, int w, int h){
	numDisplay::rePosition(x, y, w, h);

	int off_comma = (off*3.0) + nSize;
	for (int i = num_digits; i < BATTLE_NUM_DIGITS; i++) {
		digits[i]->setPosition((xPos + width - off_comma) - (nSize*(i + 1)), yPos + off);
	}
	colon->setPosition((xPos + width - (off*3.0)) - (nSize * 3), yPos + off);
}

