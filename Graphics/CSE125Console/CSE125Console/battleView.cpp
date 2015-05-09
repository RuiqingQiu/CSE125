#include "stdafx.h"
#include "battleView.h"

battleView::battleView(): gui(){
	createButtons();
}

battleView::battleView(int w, int h) : gui(w, h) {
	createButtons();
}

battleView::~battleView()
{
}

// create all the buttons on the battle view
void battleView:: createButtons(){
	// display the time left
	timer = new battleTimer(width*0.3, height - 50, 500, 50, false, false);
	timer->setScaling(true, false, width, height);
	guiItems.push_back(timer);

	healthDisplay = new healthBar(20, height - 150, 250, 25, true, false);
	guiItems.push_back(healthDisplay);

	score = new scoreBox(20, height - 100, 150, 100, true, false);
	guiItems.push_back(score);
}

void battleView::VUpdate() {
	gui::VUpdate();
	if (!updateview && isCurrentView){
		//timer->start = std::clock();
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