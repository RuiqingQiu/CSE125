#include "stdafx.h"
#include "listItem.h"
#include "Definition.h"

listItem::listItem() {
	init();
}

listItem::listItem(string filename) {
	scale = 1;
	init();
	name = filename;
	setTexture(filename, btnState::NORMAL);
	setTexture("initialize", btnState::SELECTED);
	setTexture("initialize", btnState::PRESSED);
}

listItem::listItem(string filename, int x, int y) {
	scale = 1;
	init();
	name = filename;
	setTexture(filename, btnState::NORMAL);
	setPosition(x, y);
	setTexture("initialize", btnState::SELECTED);
	setTexture("initialize", btnState::PRESSED);
}

listItem::listItem(string filename, int x, int y, bool f) {
	scale = 1;
	init();
	name = filename;
	setTexture(filename, btnState::NORMAL);
	setPosition(x, y);
	setFixed(f, f);
	setTexture("initialize", btnState::SELECTED);
	setTexture("initialize", btnState::PRESSED);
}

listItem::listItem(string filename, int x, int y, bool xf, bool yf) {
	init();
	name = filename;
	setTexture(filename, btnState::NORMAL);
	setPosition(x, y);
	setFixed(xf, yf);
	setTexture("initialize", btnState::SELECTED);
	setTexture("initialize", btnState::PRESSED);
}

listItem::listItem(string filename, int x, int y, double s) {
	scale = s;
	init();
	name = filename;
	setTexture(filename, btnState::NORMAL);
	setPosition(x, y);
	setTexture("initialize", btnState::SELECTED);
	setTexture("initialize", btnState::PRESSED);
}

listItem::listItem(string filename, int x, int y, double s, bool f) {
	scale = s;
	init();
	name = filename;
	setTexture(filename, btnState::NORMAL);
	setPosition(x, y);
	setFixed(f, f);
	setTexture("initialize", btnState::SELECTED);
	setTexture("initialize", btnState::PRESSED);
}

listItem::listItem(string filename, int x, int y, double s, bool xf, bool yf) {
	scale = s;
	init();
	name = filename;
	setTexture(filename, btnState::NORMAL);
	setPosition(x, y);
	setFixed(xf, yf);
	setTexture("initialize", btnState::SELECTED);
	setTexture("initialize", btnState::PRESSED);
}

listItem::~listItem()
{
	for (int i = 0; i < (int)subList.size(); i++) {
		delete subList[i];
	}
	subList.clear();
}

void listItem::init() {
	name = "noname";
	setPosition(0, 0);
	//default list item size
	setSize(500*scale, 100*scale);
	setFixed(false, true);
	sWidth = 0;
	sHeight = 0;
	currState = btnState::NORMAL;
	scaleX = false;
	scaleY = false;
	path = "uiItem/buttons/listItem/";
	showSubList = false;
	showPrev = false;
}

void listItem::draw() {
	if (showSubList) {
		currState = btnState::PRESSED;
	}
	else {
		currState = btnState::NORMAL;
	}
	button::draw();
	if (showSubList) {
		for (int i = 0; i < (int)subList.size(); i++) {
			subList[i]->draw();
		}
	}
}

void listItem::onClick(int state, int x, int y) {
	if (button::isSelected(x, y)) {
		button::onClick(state, x, y);
		//std::cout << identifier << std::endl;
	}
}

void listItem::rePosition(int x, int y, int w, int h) {
	button::rePosition(x, y, w, h);
	for (int i = 0; i < (int)subList.size(); i++) {
		subList[i]->rePosition(x, y, w, h);
	}
}

void listItem::onHover(int x, int y) {
	button::onHover(x, y);
	for (int i = 0; i < (int)subList.size(); i++) {
		subList[i]->onHover(x, y);
	}
}

bool listItem::isSelected(int x, int y) {
	return button::isSelected(x, y);
}

bool listItem::subSel(int x, int y) {
	for (int i = 0; i < (int)subList.size(); i++) {
		if (subList[i]->isSelected(x, y))
			return true;
	}
	return false;
}