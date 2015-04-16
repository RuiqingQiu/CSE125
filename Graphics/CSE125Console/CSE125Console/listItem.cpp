#include "stdafx.h"
#include "listItem.h"

listItem::listItem() {
	init();
}

listItem::listItem(string filename) {
	init();
	name = filename;
	setTexture(filename, false);
	texture[1] = texture[0];
}

listItem::listItem(string filename, int x, int y) {
	init();
	name = filename;
	setTexture(filename, false);
	setPosition(x, y);
	texture[1] = texture[0];
}

listItem::listItem(string filename, int x, int y, bool f) {
	init();
	name = filename;
	setTexture(filename, false);
	setPosition(x, y);
	setFixed(f, f);
	texture[1] = texture[0];
}

listItem::listItem(string filename, int x, int y, bool xf, bool yf) {
	init();
	name = filename;
	setTexture(filename, false);
	setPosition(x, y);
	setFixed(xf, yf);
	texture[1] = texture[0];
}

listItem::listItem(string filename, int x, int y, int w, int h) {
	init();
	name = filename;
	setTexture(filename, false);
	setPosition(x, y);
	setSize(w, h);
	texture[1] = texture[0];
}

listItem::listItem(string filename, int x, int y, int w, int h, bool f) {
	init();
	name = filename;
	setTexture(filename, false);
	setPosition(x, y);
	setSize(w, h);
	setFixed(f, f);
	texture[1] = texture[0];
}

listItem::listItem(string filename, int x, int y, int w, int h, bool xf, bool yf) {
	init();
	name = filename;
	setTexture(filename, false);
	setPosition(x, y);
	setSize(w, h);
	setFixed(xf, yf);
	texture[1] = texture[0];
}

listItem::~listItem()
{
}

void listItem::init() {
	name = "noname";
	setPosition(0, 0);
	setSize(100, 100);
	setFixed(false, true);
	sWidth = 0;
	sHeight = 0;
	selected = false;
	scaleX = false;
	scaleY = false;
	path = "uiItem/buttons/listItem/";
	showSubList = false;
	showPrev = false;
}

void listItem::draw() {
	button::draw();
	if (showSubList) {
		for (int i = 0; i < subList.size(); i++) {
			subList[i]->draw();
		}
	}
}

void listItem::onClick(int state, int x, int y) {
	if (isClicked(x, y)) {
		if (state == GLUT_DOWN) {
			selected = true;
		}
		if (state == GLUT_UP) {
			selected = false;
			showPrev = showSubList;
			showSubList = !showSubList;
		}
		std::cout << name.c_str() << " was clicked!" << std::endl;
	}
}

void listItem::rePosition(int x, int y, int w, int h) {
	button::rePosition(x, y, w, h);
	for (int i = 0; i < subList.size(); i++) {
		subList[i]->rePosition(x, y, w, h);
	}
}