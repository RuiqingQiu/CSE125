#include "stdafx.h"
#include "battleView.h"

battleView::battleView(): gui(){
	guiItem * text = new guiItem("text/time.jpg", 300, 300, 400, 50, false, false);
	text->setScaling(true, false, width, height);
	guiItems.push_back(text);
	//createButtons();
}

battleView::battleView(int w, int h) : gui(w, h) {
	//createButtons();
	guiItem * text = new guiItem("text/time.jpg", 300, 300, 400, 50, false, false);
	text->setScaling(true, false, width, height);
	guiItems.push_back(text);
}


battleView::~battleView()
{
}

// create all the buttons on the battle view
void battleView:: createButtons(){
	// display the time left
	cout << "Enters ! !!! in battleView.cpp" << endl;
	guiItem * text = new guiItem("text/time.jpg", 300, 300, 400, 50, false, false);
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
