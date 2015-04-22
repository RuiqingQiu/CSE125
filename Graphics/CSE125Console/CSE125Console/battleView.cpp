#include "stdafx.h"
#include "battleView.h"

battleView::battleView(): gui(){
	/*
	guiItem * text = new guiItem("text/time.jpg", 300, 300, 400, 50, false, false);
	text->setScaling(true, false, width, height);
	guiItems.push_back(text);
	*/
	createButtons();
}

battleView::battleView(int w, int h) : gui(w, h) {
	createButtons();
	/*
	guiItem * text = new guiItem("text/time.jpg", 300, 300, 400, 50, false, false);
	text->setScaling(true, false, width, height);
	guiItems.push_back(text);
	*/
}

battleView::~battleView()
{
}

// create all the buttons on the battle view
void battleView:: createButtons(){
	// display the time left
	timer = new buildTimer(width*0.3, height - 50, 400, 50, false, false);
	timer->setScaling(true, false, width, height);
	guiItems.push_back(timer);

}

void battleView::VUpdate() {
	gui::VUpdate();
	if (!updateview && isCurrentView || false) { //use true to disable timer
		timer->start = std::clock();
	}
	for (int i = 0; i < guiItems.size(); i++) {
		guiItems[i]->update();
	}
	updateview = isCurrentView;
}

	
void battleView::VOnRender() {
	GameView::VOnRender();
	set2d();
	drawAllItems();
	set3d();
}

viewType battleView::mouseClickFunc(int state, int x, int y){
	return viewType::BATTLE;
}