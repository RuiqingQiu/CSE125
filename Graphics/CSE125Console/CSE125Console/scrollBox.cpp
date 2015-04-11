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
	for (int i = 0; i < list.size(); i++) {
		list[i]->draw();
	}
}

void scrollBox::translatePos(int x, int y) {
	scrollDisplay->translatePos(x, y);
	upButton->translatePos(x, y);
	downButton->translatePos(x, y);
	for (int i = 0; i < list.size(); i++) {
		list[i]->translatePos(x, y);
	}
}

void scrollBox::addListItem(char * filename) {
	int s = list.size();
	//button jpg dimensions: 1300x300px
	//button texture orignal dimesntions: 1024x512
	//border is 10px on img
	int border = ceil ( (10.0 / 1320.0) * width );
	int w = ( (1300.0 / 1320.0) * width ) -1;
	int h = ceil ( (300.0 / 2420.0) * height );

	list.push_back(new button(filename, xPos+border, yPos + (s*h) + border, w, h));
}

bool scrollBox::isClicked() {
	return false;
}

void scrollBox::onClick() {

}