#include "stdafx.h"
#include "buildView.h"

/*
 * things to implement:
 * on click actions
 */

buildView::buildView() : gui() {
	updateview = false;
	createButtons();
}

buildView::buildView(int w, int h) : gui(w, h) {
	updateview = false;
	createButtons();
}


buildView::~buildView()
{
}

void buildView::createButtons() {
	static Cube * cube = new Cube(1);
	cube->localTransform.position = Vector3(0, 0, -5);
	cube->identifier = 1;
	PushGeoNode(cube);
	//hardcoded button sizes for now

	//text displays
	//time.jpg dimensions: 800x100
	timer = new buildTimer(width*0.3, height - 50, 400, 50, false, false);
	timer->setScaling(true, false, width, height);
	guiItems.push_back(timer);

	//text box
	//textbox.jpg dimensions: 600x400
	score = new scoreBox(20, height - 100, 150, 100, true, false);
		guiItems.push_back(score);

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

void buildView::VUpdate() {
	gui::VUpdate();
	if (!updateview && isCurrentView) {// || true) { //use true to disable timer
		timer->start = std::clock();
	}
	for (int i = 0; i < guiItems.size(); i++) {
		guiItems[i]->update();
	}
	updateview = isCurrentView;

	//update scores here
	score->deaths += 1;
	score->hits += 1;
	score->rank += 1;
	if (score->deaths == 100) score->deaths = 0;
	if (score->hits == 100) score->hits = 0;
	if (score->rank == 100) score->rank = 0;
}

void buildView::VOnRender() {
	GameView::VOnRender();
	set2d();
	drawAllItems();
	set3d();
}

void buildView::onClick(int state, int x, int y) {
	for (int i = 0; i < buttons.size(); i++) {
		//y is goes top to bottom for mouse,
		//and bottom to top for texture >.<
		buttons[i]->onClick(state, x, height-y);
	}
	if (scroll->addButton->isSelected(x, height-y) && state == GLUT_UP) {
		std::cout << "adding" << std::endl;
		int s = NodeList.size();
		Cube * cube = new Cube(1);
		cube->localTransform.position = Vector3(-s, 0, -5);
		cube->identifier = s;
		PushGeoNode(cube);
	}
	else if (scroll->removeButton->isSelected(x, height - y) && state == GLUT_UP) {
		if (NodeList.size() > 1)
			NodeList.pop_back();
	}

}

guiType buildView::switchClicked(int state, int x, int y) {
	//battle button
	if ( (buttons[0]->isSelected(x, height - y) &&
		state == GLUT_UP) || (timer->timeLeft < 0)) {
		updateview = false;
		isCurrentView = false;
		return guiType::BATTLE;
	}
	else {
		return guiType::BUILD;
	}
}

bool buildView::helpClicked(int state, int x, int y) {
	//help button
	if (state != GLUT_UP) return false;
	if (buttons[buttons.size() - 1]->isSelected(x, height - y)) {
		updateview = false;
		return true;
	}
	return false;
}

bool buildView::addBlock(int state, int x, int y) {
	return scroll->addButton->isSelected(x, y) && state == GLUT_UP;
}

bool buildView::removeBlock(int state, int x, int y) {
	return scroll->removeButton->isSelected(x, y) && state == GLUT_UP;
}