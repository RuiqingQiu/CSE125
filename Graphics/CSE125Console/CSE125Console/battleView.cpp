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
	guiItem * text = new guiItem("text/time.jpg", width*0.3, height - 50, 400, 50, false, false);
	text->setScaling(true, false, width, height);
	guiItems.push_back(text);

}

void battleView::VOnRender() {
	set2d();

	drawAllItems();

	//display the time left
	int time;

	//using drawtext for now... ugly font though
	//drawText(70, height - 15, d, 1.0, 1.0, 0.0, GLUT_BITMAP_HELVETICA_12);


	set3d();
}


void battleView::onClick(int state, int x, int y)

{}


guiType battleView::switchClicked(int state, int x, int y){
	return guiType::BATTLE;
}

// no help button in battleView
bool battleView::helpClicked(int state, int x, int y){
	return false;
}
