#include "stdafx.h"
#include "endView.h"


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

void endView::VUpdate() {
	deaths->displayValue = numDeaths;
	takedowns->displayValue = numTakedowns;
	rank->displayValue = myRank;

	gui::VUpdate();
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
}