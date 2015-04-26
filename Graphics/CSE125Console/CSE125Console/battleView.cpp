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

}

void battleView::VUpdate() {
	gui::VUpdate();
	if (!updateview && isCurrentView){
		//timer->start = std::clock();
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