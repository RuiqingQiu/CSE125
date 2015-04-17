#include "stdafx.h"
#include "buildView.h"

/*
 * things to implement:
 * on click actions
 */

buildView::buildView() : gui() {
	createButtons();
}

buildView::buildView(int w, int h) : gui(w, h) {
	createButtons();
}


buildView::~buildView()
{
}

void buildView::createButtons() {
	//hardcoded button sizes for now

	//text displays
	//time.jpg dimensions: 800x100
	guiItem * text = new guiItem("text/time.jpg", width*0.3, height - 50, 400, 50, false, false);
	text->setScaling(true, false, width, height);
	guiItems.push_back(text);

	//text box
	//textbox.jpg dimensions: 600x400
	guiItems.push_back(new guiItem("text/textbox.jpg", 20,height-100, 150, 100, true, false));

	//battle button
	button * battle = new button("menuItem/battle.jpg", width - 120, 20);
	battle->setTexture("menuItem/battle_sel.jpg", btnState::SELECTED);
	battle->setTexture("menuItem/battle_press.jpg", btnState::PRESSED);
	buttons.push_back(battle);
	
	int scale = 4;
	
	//scroll box
	//scrollbox jpg dimensions: 1000x1600px
	scroll = new scrollBox(width - 520, 100, 0.5);
	buttons.push_back(scroll);

	//list options
	for (int i = 0; i < 3; i++) {
		std::string concat = std::to_string(i) + ".jpg";
		std::string selC = std::to_string(i) + "_sel.jpg";
		scroll->addListItem(concat, selC);
		//sublist, must be added right after the parent list
		for (int j = 0; j < 3; j++) {
			concat = std::to_string((i * 10) + j) + ".jpg";
			 selC = std::to_string((i * 10) + j) + "_sel.jpg";
			scroll->addsubListItem(concat, selC);
		}
	}

	//help button
	button * help = new button("menuItem/help.jpg", 20, 20, true);
	help->setTexture("menuItem/help_sel.jpg", btnState::SELECTED);
	help->setTexture("menuItem/help_press.jpg", btnState::PRESSED);
	buttons.push_back(help);

}

void buildView::VOnRender() {
	set2d();

	drawAllItems();

	//display number vals for text... please replace with game logic numbers
	int deaths = 0;
	int hits = 0;
	int rank = 0;

	std::string d = " " + std::to_string(deaths);
	std::string h = " " + std::to_string(hits);
	std::string r = " " + std::to_string(rank);
	//using drawtext for now... ugly font though
	drawText(70, height - 15, d, 1.0, 1.0, 0.0, GLUT_BITMAP_HELVETICA_12);
	drawText(70, height - 25, h, 1.0, 1.0, 0.0, GLUT_BITMAP_HELVETICA_12);
	drawText(70, height - 35, r, 1.0, 1.0, 0.0, GLUT_BITMAP_HELVETICA_12);

	set3d();
}

void buildView::onClick(int state, int x, int y) {
	for (int i = 0; i < buttons.size(); i++) {
		//y is goes top to bottom for mouse,
		//and bottom to top for texture >.<
		buttons[i]->onClick(state, x, height-y);
	}
}

guiType buildView::switchClicked(int state, int x, int y) {
	//battle button
	if (buttons[0]->isSelected(x, height - y) &&
		state == GLUT_UP) {
		return guiType::BATTLE;
	}
	else {
		return guiType::BUILD;
	}
}

bool buildView::helpClicked(int state, int x, int y) {
	//help button
	if (state != GLUT_UP) return false;
	return buttons[buttons.size() - 1]->isSelected(x, height - y);
}

bool buildView::addBlock(int state, int x, int y) {
	return scroll->addButton->isSelected(x, y) && state == GLUT_UP;
}

bool buildView::removeBlock(int state, int x, int y) {
	return scroll->removeButton->isSelected(x, y) && state == GLUT_UP;
}