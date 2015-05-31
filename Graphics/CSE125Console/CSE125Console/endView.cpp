#include "stdafx.h"
#include "endView.h"
#include "letters.h"

endView::endView()
{
	createDisplay();
}

endView::endView(int w, int h) {
	width = w;
	height = h;
	createDisplay();
}

endView::~endView()
{
}

void endView::VOnRender() {
	set2d();
	drawAllItems();

	for (int i = 0; i < (int)roboName.size(); i++) {
		roboName[i].draw();
	}

	set3d();
}

void endView::VUpdate() {
	deaths->displayValue = numDeaths;
	takedowns->displayValue = numTakedowns;
	rank->displayValue = myRank;

	gui::VUpdate();
	for (int i = 0; i < (int) roboName.size(); i++) {
		roboName[i].update();
	}
}

void endView::createDisplay() {
	img = new background("gameOver.jpg", width, height);
	guiItems.push_back(img);

	deaths = new numDisplay("text/emptyNum.png", (width / 2.0)+100, (height / 2.0)-50, 100, 100);
	deaths->setScaling(true, true, width, height);
	guiItems.push_back(deaths);

	takedowns = new numDisplay("text/emptyNum.png", (width / 2.0) + 100, (height / 2.0) - 140, 100, 100);
	takedowns->setScaling(true, true, width, height);
	guiItems.push_back(takedowns);

	rank = new numDisplay("text/emptyNum.png", (width / 2.0) + 100, (height / 2.0) - 240, 100, 100);
	rank->setScaling(true, true, width, height);
	guiItems.push_back(rank);

	updateRobotName("no name");
}

void endView::updateRobotName(string name) {
	if (name == "") return;

	roboName.clear();

	int lSize = 50;
	int j = 0;
	for (int i = 0; i < (int)name.length(); i++) {
	int test = (int)name.at(i);
		if (test >= 97 && test <= 122) {
			//lower case letters a-z
			test = test - 97;
			roboName.push_back(letters((width / 2.0) + 25 + (lSize * i), (height / 2.0) + 145, lSize, lSize));
			//roboName[j].setScaling(true, true, width, height);
			roboName[j].letterToShow = test;
			roboName[j].offset = i;
			j++;
		}
		else if (test >= 65 && test <= 90) {
			//upper case letters a-z
			test = test - 65;
			roboName.push_back(letters(10, 10, lSize, lSize));
			roboName.push_back(letters((width / 2.0) + 25 + (lSize * i), (height / 2.0) + 145, lSize, lSize));
			roboName[j].letterToShow = test;
			roboName[j].offset = i;
			j++;
		}
	}
}
