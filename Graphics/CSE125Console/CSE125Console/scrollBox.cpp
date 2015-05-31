#include "stdafx.h"
#include "scrollBox.h"


scrollBox::scrollBox(){
	scrollDisplay = new guiItem("scrollbox.jpg");
	setPosition(0, 0);
	setFixed(false, true);
	scale = 1;
	init();
}

scrollBox::scrollBox(int x, int y) {
	scrollDisplay = new guiItem("scrollbox.jpg", x, y);
	setPosition(x, y);
	setFixed(false, true);
	scale = 1;
	init();
}

scrollBox::scrollBox(int x, int y, bool f) {
	scrollDisplay = new guiItem("scrollbox.jpg", x, y, f);
	setPosition(x, y);
	setFixed(f, f);
	scale = 1;
	init();
}

scrollBox::scrollBox(int x, int y, bool xf, bool yf) {
	scrollDisplay = new guiItem("scrollbox.jpg", x, y, xf, yf);
	setPosition(x, y);
	setFixed(xf, yf);
	scale = 1;
	init();
}

scrollBox::scrollBox(int x, int y, double s) {
	scrollDisplay = new guiItem("scrollbox.jpg", x, y, int(default_w*s), int(default_h*s));
	setPosition(x, y);
	setFixed(false, true);
	scale = s;
	init();
}

scrollBox::scrollBox(int x, int y, double s, bool f) {
	scrollDisplay = new guiItem("scrollbox.jpg", x, y, default_w*s, default_h*s, f);
	setPosition(x, y);
	setFixed(f, f);
	scale = s;
	init();
}

scrollBox::scrollBox(int x, int y, double s, bool xf, bool yf) {
	scrollDisplay = new guiItem("scrollbox.jpg", x, y, default_w*s, default_h*s, xf, yf);
	setPosition(x, y);
	setFixed(xf, yf);
	scale = s;
	init();
}

scrollBox::~scrollBox()
{
	for (int i = 0; i < (int)list.size(); i++) {
		delete list[i];
	}
	list.clear();
}


void scrollBox::init() {
	displayIdx = 0;
	setSize(default_w * scale, default_h * scale);

	//create "add and "remove" buttons
	int xoff = xPos + (100 * scale);
	int yoff = yPos + (35 * scale);
	addButton = new button("scrollbox/add.jpg", xoff, yoff);
	addButton->setTexture("scrollbox/add_sel.jpg", btnState::SELECTED);
	addButton->setTexture("scrollbox/add_press.jpg", btnState::PRESSED);

	xoff += (600 * scale);
	removeButton = new button("scrollbox/remove.jpg", xoff, yoff);
	removeButton->setTexture("scrollbox/remove_sel.jpg", btnState::SELECTED);
	removeButton->setTexture("scrollbox/remove_press.jpg", btnState::PRESSED);

	yoff = yPos + height - (85 * scale);
	clearButton = new button("scrollbox/clear.jpg", xoff, yoff);
	clearButton->setTexture("scrollbox/clear_sel.jpg", btnState::SELECTED);
	clearButton->setTexture("scrollbox/clear_press.jpg", btnState::PRESSED);

	//keep ratio to scroll box dimensions: 1320x2420px
	//int ratio = height / 24.2;
	//button jpg dimensions: 1320x100px
	//button texture orignal dimesntions: 1024x128
	//upButton = new button("scrollbox/up.jpg", xPos, yPos+height, width, ratio);
	//upButton->setTexture("scrollbox/up_sel.jpg", true);

	//button jpg dimensions: 1320x100px
	//button texture orignal dimesntions: 1024x128
	//downButton = new button("scrollbox/down.jpg", xPos, yPos-ratio, width, ratio);
	//downButton->setTexture("scrollbox/down_sel.jpg", true);
}

void scrollBox::draw() {
	scrollDisplay->draw();
	//upButton->draw();
	//downButton->draw();
	addButton->draw();
	removeButton->draw();
	clearButton->draw();
	for (int i = displayIdx; i < displayIdx + MAXDISPLAY; i++) {
		if (i >= (int)list.size()) break;
		list[i]->draw();
	}
}

void scrollBox::rePosition(int x, int y, int w, int h) {
	scrollDisplay->rePosition(x, y, w, h);
	//upButton->rePosition(x, y, w, h);
	//downButton->rePosition(x, y, w, h);
	addButton->rePosition(x, y, w, h);
	removeButton->rePosition(x, y, w, h);
	clearButton->rePosition(x, y, w, h);
	for (int i = 0; i < (int)list.size(); i++) {
		list[i]->rePosition(x, y, w, h);
	}
}

int scrollBox::getTotalSize() {
	int s = list.size();
	for (int i = 0; i < (int)list.size(); i++) {
		s += list[i]->subList.size();
	}
	return s;
}

void scrollBox::addListItem(string filename, string fileType, bool hasSel, bool hasPress) {
	int s = list.size();
	s = MAXDISPLAY - 1 - s;
	//header area is 100 pixels, footer area is 100 pixels
	double hf = 200.0 * scale;
	double h = ((height - hf) / MAXDISPLAY);

	listItem * newL = new listItem(filename+fileType, xPos, yPos + int(s*h + (hf / 2.0)), scale);
	if (hasSel) {
		newL->setTexture(filename+"_sel"+fileType, btnState::SELECTED);
	}
	if (hasPress) {
		newL->setTexture(filename + "_press" + fileType, btnState::PRESSED);
	}
	else {
		newL->setTexture("initialize", btnState::PRESSED);
	}
	list.push_back(newL);
}

void scrollBox::addsubListItem(string filename, string fileType, int id, bool hasSel, bool hasPress) {
	int s = list[list.size()-1]->subList.size();
	s = MAXDISPLAY - 1 - s;
	//header area is 100 pixels, footer area is 100 pixels
	double hf = 200.0 * scale;
	double h = ((height - hf) / MAXDISPLAY);
	double half = (default_w/2.0) * scale;

	listItem * newSl = new listItem(filename+fileType, int(xPos + half), yPos + int(s*h + (hf / 2.0)), scale);
	if (hasSel) {
		newSl->setTexture(filename + "_sel" + fileType, btnState::SELECTED);
	}
	if (hasPress) {
		newSl->setTexture(filename + "_press" + fileType, btnState::PRESSED);
	}
	else {
		newSl->setTexture("initialize", btnState::PRESSED);
	}
	newSl->identifier = id;
	list[list.size() - 1]->subList.push_back(newSl);
}

bool scrollBox::isSelected(int x, int y) {
	//if (upButton->isSelected(x, y)) return true;
	//if (downButton->isSelected(x, y)) return true;

	for (int i = 0; i < (int)list.size(); i++) {
		if (list[i]->isSelected(x, y)) return true;
	}

	return false;
}

void scrollBox::onClick(int state, int x, int y) {
	int h = height / MAXDISPLAY;

	/*
	if (upButton->isSelected(x, y)) {
		if (list.size() <= MAXDISPLAY) return;
		if (displayIdx == 0) return;
		displayIdx--;
		for (int i = 0; i < list.size(); i++) {
			list[i]->translate(0, -h);
		}
	}
	if (downButton->isSelected(x, y)) {
		int s = list.size();
		if (s <= MAXDISPLAY/2) return;
		if ((s - displayIdx) <= MAXDISPLAY/2) return;
		displayIdx++;
		for (int i = 0; i < list.size(); i++) {
			list[i]->translate(0, h);
		}
	}
	*/

	//upButton->onClick(state, x, y);
	//downButton->onClick(state, x, y);
	addButton->onClick(state, x, y);
	removeButton->onClick(state, x, y);
	clearButton->onClick(state, x, y);
	if (addButton->isSelected(x, y) || removeButton->isSelected(x, y)) return;
	for (int i = displayIdx; i < displayIdx+MAXDISPLAY; i++) {
		if (i >= (int)list.size()) return;
		if (!list[i]->subSel(x, y))
			list[i]->showSubList = false;
		if (list[i]->isSelected(x, y) && state == GLUT_UP) {
			list[i]->showSubList = true;
		}
		list[i]->onClick(state, x, y);
		if (list[i]->showSubList) {
			for (int j = 0; j < (int)list[i]->subList.size(); j++) {
				list[i]->subList[j]->showSubList = false;
				list[i]->subList[j]->onClick(state, x, y);
				if (list[i]->subList[j]->isSelected(x, y) && state == GLUT_UP) {
					list[i]->subList[j]->showSubList = true;
					currentSelection = list[i]->subList[j]->identifier;
					break;
				}
			}
		}
	}
}

void scrollBox::onHover(int x, int y) {
	for (int i = 0; i < (int)list.size(); i++) {
		list[i]->onHover(x, y);
	}
	addButton->onHover(x, y);
	removeButton->onHover(x, y);
}