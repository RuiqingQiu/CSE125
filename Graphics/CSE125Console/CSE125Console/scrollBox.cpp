#include "stdafx.h"
#include "scrollBox.h"


scrollBox::scrollBox(){
	scrollDisplay = new guiItem("scrollbox/scrollbox.jpg");
	xPos = 0;
	yPos = 0;
	xfixed = false;
	yfixed = true;
	init();
}

scrollBox::scrollBox(int x, int y) {
	scrollDisplay = new guiItem("scrollbox.jpg", x, y);
	xPos = x;
	yPos = y;
	xfixed = false;
	yfixed = true;
	init();
}

scrollBox::scrollBox(int x, int y, bool f) {
	scrollDisplay = new guiItem("scrollbox.jpg", x, y, f);
	xPos = x;
	yPos = y;
	xfixed = f;
	yfixed = f;
	init();
}

scrollBox::scrollBox(int x, int y, bool xf, bool yf) {
	scrollDisplay = new guiItem("scrollbox.jpg", x, y, xf, yf);
	xPos = x;
	yPos = y;
	xfixed = xf;
	yfixed = yf;
	init();
}

scrollBox::scrollBox(int x, int y, int w, int h) {
	scrollDisplay = new guiItem("scrollbox.jpg", x, y, w, h);
	xPos = x;
	yPos = y;
	xfixed = false;
	yfixed = true;
	width = w;
	height = h;
	init();
}

scrollBox::scrollBox(int x, int y, int w, int h, bool f) {
	scrollDisplay = new guiItem("scrollbox.jpg", x, y, w, h, f);
	xPos = x;
	yPos = y;
	width = w;
	height = h;
	xfixed = f;
	yfixed = f;
	init();
}

scrollBox::scrollBox(int x, int y, int w, int h, bool xf, bool yf) {
	scrollDisplay = new guiItem("scrollbox.jpg", x, y, w, h, xf, yf);
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
	upButton = new button("scrollbox/up.jpg", xPos, yPos+height, width, ratio);
	upButton->setTexture("scrollbox/up_sel.jpg", true);

	//button jpg dimensions: 1320x100px
	//button texture orignal dimesntions: 1024x128
	downButton = new button("scrollbox/down.jpg", xPos, yPos-ratio, width, ratio);
	downButton->setTexture("scrollbox/down_sel.jpg", true);
}

void scrollBox::draw() {
	scrollDisplay->draw();
	upButton->draw();
	downButton->draw();
	for (int i = displayIdx; i < displayIdx + MAXDISPLAY; i++) {
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

int scrollBox::getTotalSize() {
	int s = list.size();
	for (int i = 0; i < list.size(); i++) {
		s += list[i]->subList.size();
	}
	return s;
}

void scrollBox::addListItem(string filename) {
	int s = list.size();
	s = MAXDISPLAY - 1 - s;
	int h = height / MAXDISPLAY;

	list.push_back(new listItem(filename, xPos, yPos + (s*h), width, h));
}

void scrollBox::addsubListItem(string filename) {
	int s = list.size()+ list[list.size()-1]->subList.size();
	s = MAXDISPLAY -1 - s;
	int h = height / MAXDISPLAY;

	list[list.size()-1]->subList.push_back(new listItem("subItem/"+filename, xPos, yPos + (s*h), width, h));
}

bool scrollBox::isClicked(int x, int y) {
	if (upButton->isClicked(x, y)) return true;
	if (downButton->isClicked(x, y)) return true;

	for (int i = 0; i < list.size(); i++) {
		if (list[i]->isClicked(x, y)) return true;
	}

	return false;
}

void scrollBox::onClick(int state, int x, int y) {
	int h = height / MAXDISPLAY;

	if (upButton->isClicked(x, y)) {
		if (list.size() <= MAXDISPLAY) return;
		if (displayIdx == 0) return;
		displayIdx--;
		for (int i = 0; i < list.size(); i++) {
			list[i]->translate(0, -h);
		}
	}
	if (downButton->isClicked(x, y)) {
		int s = list.size();
		if (s <= MAXDISPLAY/2) return;
		if ((s - displayIdx) <= MAXDISPLAY/2) return;
		displayIdx++;
		for (int i = 0; i < list.size(); i++) {
			list[i]->translate(0, h);
		}
	}

	upButton->onClick(state, x, y);
	downButton->onClick(state, x, y);
	for (int i = displayIdx; i < displayIdx+MAXDISPLAY; i++) {
		if (i >= list.size()) return;
		list[i]->onClick(state, x, y);
		int s = list[i]->subList.size();
		if (list[i]->showSubList && state == GLUT_UP) {
			for (int j = i + 1; j < list.size(); j++) {
				list[j]->translate(0, -h*s);
			}
		}
		else if (!list[i]->showSubList && list[i]->showPrev && state == GLUT_UP) {
			for (int j = i + 1; j < list.size(); j++) {
				list[j]->translate(0, h*s);
			}
		}
	}
}