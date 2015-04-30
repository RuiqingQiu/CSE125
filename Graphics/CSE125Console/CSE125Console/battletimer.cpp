#include "stdafx.h"
#include "battletimer.h"


string battleTimer::textPath = "text/time_long.jpg";
battleTimer::battleTimer() : guiItem() {
	createNumbers();
}

battleTimer::battleTimer(int x, int y) :
guiItem(textPath, x, y) {
	createNumbers();
}

battleTimer::battleTimer(int x, int y, bool f) :
guiItem(textPath, x, y, f) {
	createNumbers();
}

battleTimer::battleTimer(int x, int y, bool xf, bool yf) :
guiItem(textPath, x, y, xf, yf) {
	createNumbers();
}
battleTimer::battleTimer(int x, int y, int w, int h) :
guiItem(textPath, x, y, w, h) {
	createNumbers();
}

battleTimer::battleTimer(int x, int y, int w, int h, bool f) :
guiItem(textPath, x, y, w, h, f) {
	createNumbers();
}

battleTimer::battleTimer(int x, int y, int w, int h, bool xf, bool yf) :
guiItem(textPath, x, y, w, h, xf, yf) {
	createNumbers();
}

battleTimer::~battleTimer() {
}


void battleTimer::createNumbers(){
	secLeft = MAX_TIME;
	minLeft = MIN;
	start = std::clock();
	double off = (10.0 / 100.0) * height;
	int nSize = height - (off*2.0);

	for (int i = 0; i < DIGITS; i++){
		digits[i] = new numbers((xPos + width - off) - (nSize*(i + 1)), yPos + off, nSize, nSize, xfixed, yfixed);
	}
	int off_comma = off + nSize;

	for (int i = DIGITS; i < NUM_DIGITS; i++) {
		digits[i] = new numbers((xPos + width - off_comma) - (nSize*(i + 1)), yPos + off, nSize, nSize, xfixed, yfixed);
	}
}

void battleTimer::update(){
	// convert the time used to second
	int timeUsed = (std::clock() - start) / CLOCKS_PER_SEC;
	// mod gives the reminder
	int sec = timeUsed % MAX_TIME; // sec used
	int min = (timeUsed - sec) / MAX_TIME;// mins used

	// if minLeft is less then 0, don't update anymore
	if (minLeft <= -1){
		secLeft = 0;
		cout << "Enter " << endl;
		//return;
	}
	// if still time left 
	else{
		minLeft = MIN - min; // calcualte the min left
		cout << "minLeft " << minLeft << endl;
		secLeft = MAX_TIME - sec;
		cout << "secLeft " << secLeft << endl;
	}
	int idx_sec = secLeft;
	int idx = minLeft;

	 // update sec first
	for (int i = 0; i < DIGITS; i++) {
		if (!(idx_sec >= 0)) break;
		int digit = idx_sec % 10;
		digits[i]->numIdx = digit;
		idx_sec /= 10;

	}
	// then update minutes
	for (int i = DIGITS; i < NUM_DIGITS; i++) {
		if (!(idx >= 0)) break;
		int digit = idx % 10;
		digits[i]->numIdx = digit;
		idx /= 10;
	}
}


void battleTimer::draw(){
	guiItem::draw();
	for (int i = 0; i < NUM_DIGITS; i++) {
		digits[i]->draw();
	}
	double off = (10.0 / 100.0) * height;
	int nSize = height - (off*2.0);
	//add one comma and draw
	//guiItem* comma = new guiItem("text/symbols/colon.jpg", 945,970,nSize,nSize); // all things have the same size 
	guiItem* comma = new guiItem("text/symbols/colon.jpg", (xPos + width - off) - (nSize * 3), yPos + off, nSize, nSize); // all things have the same size 
	comma->draw();
}


void battleTimer::rePosition(int x, int y, int w, int h){
	guiItem::rePosition(x, y, w, h);
	double off = (10.0 / 100.0) * height;
	int nSize = height - (off*2.0);
	for (int i = 0; i < DIGITS; i++){
		digits[i] = new numbers((xPos + width - off) - (nSize*(i + 1)), yPos + off, nSize, nSize, xfixed, yfixed);
	}

	guiItem* comma = new guiItem("text/symbols/colon.jpg", (xPos + width - off) - (nSize * 3), yPos + off, nSize, nSize); // all things have the same size 
	int off_comma = off + nSize;

	for (int i = DIGITS; i < NUM_DIGITS; i++) {
		digits[i] = new numbers((xPos + width - off_comma) - (nSize*(i + 1)), yPos + off, nSize, nSize, xfixed, yfixed);
	}
}

