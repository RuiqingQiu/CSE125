#include "stdafx.h"
#include "loadDisplay.h"

string loadDisplay::textPath = "text/loadingCircle.png";

loadDisplay::loadDisplay()
{
}

loadDisplay::loadDisplay(int x, int y) :
guiItem(textPath, x, y) {
	createText();
}

loadDisplay::loadDisplay(int x, int y, bool f) :
guiItem(textPath, x, y, f) {
	createText();
}

loadDisplay::loadDisplay(int x, int y, bool xf, bool yf) :
guiItem(textPath, x, y, xf, yf) {
	createText();
}
loadDisplay::loadDisplay(int x, int y, int w, int h) :
guiItem(textPath, x, y, w, h) {
	createText();
}

loadDisplay::loadDisplay(int x, int y, int w, int h, bool f) :
guiItem(textPath, x, y, w, h, f) {
	createText();
}

loadDisplay::loadDisplay(int x, int y, int w, int h, bool xf, bool yf) :
guiItem(textPath, x, y, w, h, xf, yf) {
	createText();
}

loadDisplay::~loadDisplay()
{
}

void loadDisplay::createText() {
	rotation = 360;
	loadingText = new guiItem("text/loadingText.jpg", xPos + (width * 100.0/500.0) , yPos + (height * 220.0/500.0), int(width * 300.0/500.0), int(height * 60.0/500.0), scaleX, scaleY);
}

void loadDisplay::update() {
	rotation -= 1;
	if (rotation < 0) rotation = 360;
}

void loadDisplay::draw() {
	guiItem::draw();
	loadingText->draw();
}

void loadDisplay::rePosition(int x, int y, int w, int h) {
	guiItem::rePosition(x, y, w, h);

	loadingText->setPosition(xPos + int(width * 100.0 / 500.0), yPos + int(height * 220.0 / 500.0));
}