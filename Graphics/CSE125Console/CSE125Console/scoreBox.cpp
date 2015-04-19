#include "stdafx.h"
#include "scoreBox.h"

string scoreBox::textPath = "text/scorebox.jpg";

double scoreBox::border = 53.0 / 400.0;
double scoreBox::spacing = 58.0 / 400.0;
double scoreBox::sizing = 60.0 / 400.0;

scoreBox::scoreBox() : guiItem() {
	createNumbers();
}

scoreBox::scoreBox(int x, int y) :
guiItem(textPath, x, y) {
	createNumbers();
}

scoreBox::scoreBox(int x, int y, bool f) :
guiItem(textPath, x, y, f) {
	createNumbers();
}

scoreBox::scoreBox(int x, int y, bool xf, bool yf) :
guiItem(textPath, x, y, xf, yf) {
	createNumbers();
}
scoreBox::scoreBox(int x, int y, int w, int h) :
guiItem(textPath, x, y, w, h) {
	createNumbers();
}

scoreBox::scoreBox(int x, int y, int w, int h, bool f) :
guiItem(textPath, x, y, w, h, f) {
	createNumbers();
}

scoreBox::scoreBox(int x, int y, int w, int h, bool xf, bool yf) :
guiItem(textPath, x, y, w, h, xf, yf) {
	createNumbers();
}

scoreBox::~scoreBox()
{
}

void scoreBox::createNumbers() {
	deaths = 0;
	hits = 0;
	rank = 0;

	double off = scoreBox::border  * height;
	double offset = scoreBox::spacing * height;
	int nSize = scoreBox::sizing * height;
	for (int i = 0; i < MAX_DIGITS; i++) {
		rankDigits[i] = new numbers((xPos + width - off) - (nSize*(i + 1)), yPos + off, nSize, nSize, xfixed, yfixed);
		hitDigits[i] = new numbers((xPos + width - off) - (nSize*(i + 1)), yPos + off + nSize + offset, nSize, nSize, xfixed, yfixed);
		deathDigits[i] = new numbers((xPos + width - off) - (nSize*(i + 1)), yPos + off + ((nSize + offset)*2), nSize, nSize, xfixed, yfixed);
	}
}

void scoreBox::update() {
	//update score here
	int idx = deaths;
	for (int i = 0; i < MAX_DIGITS; i++) {
		if (!(idx >= 0)) break;
		int digit = idx % 10;
		rankDigits[i]->numIdx = digit;
		idx /= 10;
	}
	idx = hits;
	for (int i = 0; i < MAX_DIGITS; i++) {
		if (!(idx >= 0)) break;
		int digit = idx % 10;
		hitDigits[i]->numIdx = digit;
		idx /= 10;
	}
	idx = deaths;
	for (int i = 0; i < MAX_DIGITS; i++) {
		if (!(idx >= 0)) break;
		int digit = idx % 10;
		deathDigits[i]->numIdx = digit;
		idx /= 10;
	}
	
}

void scoreBox::draw() {
	guiItem::draw();
	for (int i = 0; i < MAX_DIGITS; i++) {
		rankDigits[i]->draw();
		hitDigits[i]->draw();
		deathDigits[i]->draw();
	}
}

void scoreBox::rePosition(int x, int y, int w, int h) {
	guiItem::rePosition(x, y, w, h);
	/*
	for (int i = 0; i < NUM_DIGITS; i++) {
	digits[i].rePosition(x, y, w, h);
	}
	*/
	double off = scoreBox::border  * height;
	double offset = scoreBox::spacing * height;
	int nSize = scoreBox::sizing * height;
	//want to manually make sure it stays relative to time left box
	for (int i = 0; i < MAX_DIGITS; i++) {
		rankDigits[i]->setPosition((xPos + width - off) - (nSize*(i + 1)), yPos + off);
		hitDigits[i]->setPosition((xPos + width - off) - (nSize*(i + 1)), yPos + off+nSize+offset);
		deathDigits[i]->setPosition((xPos + width - off) - (nSize*(i + 1)), yPos + off+((nSize+offset)*2));
	}
}