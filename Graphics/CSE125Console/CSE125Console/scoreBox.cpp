#include "stdafx.h"
#include "scoreBox.h"

string scoreBox::textPath = "text/scorebox.jpg";

double scoreBox::border = 40.0 / 400.0;
double scoreBox::spacing = 15.0 / 400.0;
double scoreBox::sizing = 75.0 / 400.0;

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

int scoreBox::getDeaths() {
	return deaths;
}

int scoreBox::getTakedowns() {
	return kills;
}

int scoreBox::getRank() {
	return rank;
}

void scoreBox::createNumbers() {
	deaths = 0;
	kills = 0;
	rank = 0;
	money = 40000;

	double off = scoreBox::border  * height;
	double offset = scoreBox::spacing * height;
	int nSize = scoreBox::sizing * height; 

	killsDisplay = new numDisplay("text/emptyNum.png", xPos + width - off - (nSize * 2), yPos + off + (nSize * 3) + (offset * 3), nSize * 2, nSize, true, false);
	deathDisplay = new numDisplay("text/emptyNum.png", xPos + width - off - (nSize * 2), yPos + off + (nSize * 2) + (offset * 2), nSize * 2, nSize, true, false);
	rankDisplay  = new numDisplay("text/emptyNum.png", xPos + width - off - (nSize * 2), yPos + off + (nSize * 1) + (offset * 1), nSize * 2, nSize, true, false);

	moneyDisplay = new numDisplay("text/emptyNum.png", xPos + width - off - (nSize * 4), yPos + off + (nSize * 0) + (offset * 0), nSize * 4, nSize, true, false, 4);

	numbers.push_back(killsDisplay);
	numbers.push_back(deathDisplay);
	numbers.push_back(rankDisplay);
	numbers.push_back(moneyDisplay);
}

void scoreBox::update() {
	//update score here
	killsDisplay->displayValue = kills;
	deathDisplay->displayValue = deaths;
	rankDisplay->displayValue = rank;
	moneyDisplay->displayValue = money;

	for (int i = 0; i < 4; i++) {
		numbers[i]->update();
	}
	
}

void scoreBox::updateScore(int d, int h, int r, int m) {
	deaths = d;
	kills = h;
	rank = r;
	money = m;
}

void scoreBox::updateScore(int d, int h, int r) {
	deaths = d;
	kills = h;
	rank = r;
}

void scoreBox::draw() {
	guiItem::draw();
	for (int i = 0; i < 4; i++) {
		numbers[i]->draw();
	}
}

void scoreBox::rePosition(int x, int y, int w, int h) {
	guiItem::rePosition(x, y, w, h);

	double off = scoreBox::border  * height;
	double offset = scoreBox::spacing * height;
	int nSize = scoreBox::sizing * height;

	//want to manually make sure it stays relative to time left box
	for (int i = 0; i < 4; i++) {
		numbers[i]->rePosition(x, y, w, h);
	}
}