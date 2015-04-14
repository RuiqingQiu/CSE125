#include "stdafx.h"
#include "scrollBox.h"


scrollBox::scrollBox(){
	scrollDisplay = new guiItem("uiItem/scrollbox/scrollbox.jpg");
	xPos = 0;
	yPos = 0;
	xfixed = false;
	yfixed = true;
	init();
}

scrollBox::scrollBox(int x, int y) {
	scrollDisplay = new guiItem("uiItem/scrollbox/scrollbox.jpg", x, y);
	xPos = x;
	yPos = y;
	xfixed = false;
	yfixed = true;
	init();
}

scrollBox::scrollBox(int x, int y, bool f) {
	scrollDisplay = new guiItem("uiItem/scrollbox/scrollbox.jpg", x, y, f);
	xPos = x;
	yPos = y;
	xfixed = f;
	yfixed = f;
	init();
}

scrollBox::scrollBox(int x, int y, bool xf, bool yf) {
	scrollDisplay = new guiItem("uiItem/scrollbox/scrollbox.jpg", x, y, xf, yf);
	xPos = x;
	yPos = y;
	xfixed = xf;
	yfixed = yf;
	init();
}

scrollBox::scrollBox(int x, int y, int w, int h) {
	scrollDisplay = new guiItem("uiItem/scrollbox/scrollbox.jpg", x, y, w, h);
	xPos = x;
	yPos = y;
	xfixed = false;
	yfixed = true;
	width = w;
	height = h;
	init();
}

scrollBox::scrollBox(int x, int y, int w, int h, bool f) {
	scrollDisplay = new guiItem("uiItem/scrollbox/scrollbox.jpg", x, y, w, h, f);
	xPos = x;
	yPos = y;
	width = w;
	height = h;
	xfixed = f;
	yfixed = f;
	init();
}

scrollBox::scrollBox(int x, int y, int w, int h, bool xf, bool yf) {
	scrollDisplay = new guiItem("uiItem/scrollbox/scrollbox.jpg", x, y, w, h, xf, yf);
	xPos = x;
	yPos = y;
	width = w;
	height = h;
	xfixed = xf;
	yfixed = yf;
	init();
}

scrollBox::~scrollBox()
{
}


void scrollBox::init() {
	displayIdx = 0;
	//keep ratio to scroll box dimensions: 1320x2420px
	int ratio = height / 24.2;
	//button jpg dimensions: 1320x100px
	//button texture orignal dimesntions: 1024x128
	upButton = new button("uiItem/scrollbox/up.jpg", xPos, yPos+height, width, ratio);

	//button jpg dimensions: 1320x100px
	//button texture orignal dimesntions: 1024x128
	downButton = new button("uiItem/scrollbox/down.jpg", xPos, yPos-ratio, width, ratio);
}

void scrollBox::draw() {
	scrollDisplay->draw();
	upButton->draw();
	downButton->draw();
	for (int i = displayIdx; i < displayIdx+8; i++) {
		if (i >= list.size()) break;
		list[i]->draw();
	}
}

void scrollBox::rePosition(int x, int y, int w, int h) {
	scrollDisplay->rePosition(x, y, w, h);
	upButton->rePosition(x, y, w, h);
	downButton->rePosition(x, y, w, h);
	for (int i = 0; i < list.size(); i++) {
		list[i]->rePosition(x, y, w, h);
	}
}

void scrollBox::addListItem(char * filename) {
	int s = list.size();
	s = 7 - s;
	//button jpg dimensions: 1300x300px
	//button texture orignal dimesntions: 1024x512
	//border is 10px on img
	int border = ceil ( (10.0 / 1320.0) * width );
	int w = ( (1300.0 / 1320.0) * width ) -1;
	int h = ceil ( (300.0 / 2420.0) * height );

	list.push_back(new button(filename, xPos+border, yPos + (s*h) + border, w, h));
}

bool scrollBox::isClicked(int x, int y) {
	if (upButton->isClicked(x, y)) return true;
	if (downButton->isClicked(x, y)) return true;

	for (int i = 0; i < list.size(); i++) {
		if (list[i]->isClicked(x, y)) return true;
	}

	return false;
}

void scrollBox::onClick(int x, int y) {
	int border = ceil((10.0 / 1320.0) * width);
	int h = ceil((300.0 / 2420.0) * height);

	if (upButton->isClicked(x, y)) {
		if (list.size() <= 8) return;
		if (displayIdx == 0) return;
		displayIdx--;
		for (int i = 0; i < list.size(); i++) {
			list[i]->translate(0, -(h + border));
		}
	}
	if (downButton->isClicked(x, y)) {
		int s = list.size();
		if (s <= 4) return;
		if ((s - displayIdx) <= 4) return;
		displayIdx++;
		for (int i = 0; i < list.size(); i++) {
			list[i]->translate(0, h+border);
		}
	}

	upButton->onClick(x, y);
	downButton->onClick(x, y);
	for (int i = displayIdx; i < displayIdx+8; i++) {
		if (i >= list.size()) return;
		list[i]->onClick(x, y);
	}
}