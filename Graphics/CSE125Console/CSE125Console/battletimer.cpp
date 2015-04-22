#include "stdafx.h"
#include "battletimer.h"

battleTimer::battleTimer() : buildTimer() {
	createNumbers();
}

battleTimer::battleTimer(int x, int y) :
buildTimer(x, y) {
	createNumbers();
}

battleTimer::battleTimer(int x, int y, bool f) :
buildTimer(x, y, f) {
	createNumbers();
}

battleTimer::battleTimer(int x, int y, bool xf, bool yf) :
buildTimer(x, y, xf, yf) {
	createNumbers();
}
battleTimer::battleTimer(int x, int y, int w, int h) :
buildTimer(x, y, w, h) {
	createNumbers();
}

battleTimer::battleTimer(int x, int y, int w, int h, bool f) :
buildTimer(x, y, w, h, f) {
	createNumbers();
}

battleTimer::battleTimer(int x, int y, int w, int h, bool xf, bool yf) :
buildTimer(x, y, w, h, xf, yf) {
	createNumbers();
}

battleTimer::~battleTimer() {
}

void battleTimer::update(){
	// this is updating seconds
	timeLeft = MAX_TIME - ((std::clock() - start) / CLOCKS_PER_SEC);
	int idx = timeLeft;
	for (int i = 0; i < NUM_DIGITS; i++) {
		if (!(idx >= 0)) break;
		int digit = idx % 10;
		digits[i]->numIdx = digit;
		idx /= 10;
	}
    // need to update minutes as well
}


void battleTimer::draw(){
	guiItem::draw();
	for (int i = 0; i < NUM_DIGITS; i++) {
		digits[i]->draw();
	}
	//add one comma and draw
	guiItem* comma = new guiItem("text/symbols/colon.jpg", 300,300);
	comma->draw();

}


void battleTimer::rePosition(int x, int y, int w, int h){
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
		digits[i]->setPosition((xPos + width - off) - (nSize*(i + 1)), yPos + off);
	}
}

