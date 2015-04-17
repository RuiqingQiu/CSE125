#include "stdafx.h"
#include "listItem.h"

listItem::listItem() {
	init();
}

listItem::listItem(string filename) {
	scale = 1;
	init();
	name = filename;
	setTexture(filename, btnState::NORMAL);
	texture[1] = texture[0];
}

listItem::listItem(string filename, int x, int y) {
	scale = 1;
	init();
	name = filename;
	setTexture(filename, btnState::NORMAL);
	setPosition(x, y);
	texture[1] = texture[0];
}

listItem::listItem(string filename, int x, int y, bool f) {
	scale = 1;
	init();
	name = filename;
	setTexture(filename, btnState::NORMAL);
	setPosition(x, y);
	setFixed(f, f);
	texture[1] = texture[0];
}

listItem::listItem(string filename, int x, int y, bool xf, bool yf) {
	init();
	name = filename;
	setTexture(filename, btnState::NORMAL);
	setPosition(x, y);
	setFixed(xf, yf);
	texture[1] = texture[0];
}

listItem::listItem(string filename, int x, int y, double s) {
	scale = s;
	init();
	name = filename;
	setTexture(filename, btnState::NORMAL);
	setPosition(x, y);
	texture[1] = texture[0];
}

listItem::listItem(string filename, int x, int y, double s, bool f) {
	scale = s;
	init();
	name = filename;
	setTexture(filename, btnState::NORMAL);
	setPosition(x, y);
	setFixed(f, f);
	texture[1] = texture[0];
}

listItem::listItem(string filename, int x, int y, double s, bool xf, bool yf) {
	scale = s;
	init();
	name = filename;
	setTexture(filename, btnState::NORMAL);
	setPosition(x, y);
	setFixed(xf, yf);
	texture[1] = texture[0];
}

listItem::~listItem()
{
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
		currState = btnState::SELECTED;
	}
	button::draw();
	if (showSubList) {
		for (int i = 0; i < subList.size(); i++) {
			subList[i]->draw();
		}
	}
}

void listItem::onClick(int state, int x, int y) {
	button::onClick(state, x, y);
}

void listItem::rePosition(int x, int y, int w, int h) {
	button::rePosition(x, y, w, h);
	for (int i = 0; i < subList.size(); i++) {
		subList[i]->rePosition(x, y, w, h);
	}
}

void listItem::onHover(int x, int y) {
	button::onHover(x, y);
	for (int i = 0; i < subList.size(); i++) {
		subList[i]->onHover(x, y);
	}
}