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


buildView::~buildView() {
}

void buildView::createButtons() {
	center = Vector3(-5, -5, -5);
	//center = Vector3(0, 0, -5);
	static Cube * cube = new Cube(1);
	cube->localTransform.position = center;
	cube->identifier = 4;
	mappings[4] = true;
	currentBlock = 4;
	PushGeoNode(cube);
	currentNode = nullptr;  //not allowed to move base cube
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
	if (!updateview && isCurrentView || true) { //use true to disable timer
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

Vector3 buildView::addNewNodePos() {
	//for now, just add to the right of current node
	//logic here for finding place to start new node
	Vector3 check;

	if (currentNode == nullptr)
		check = translateNode(Vector3(1, 0, 0), NodeList[0]);
	else
		check = translateNode(Vector3(1, 0, 0), currentNode);

	if (currentNode != nullptr) {
		Vector3 temp = currentNode->localTransform.position;
		//if we got same position, try to the left
		if (check.equals(temp)) {
			check = translateNode(Vector3(-1, 0, 0), currentNode);
			//if still invalid, fuck it just don't add for now
			if (check.equals(temp)) {
				return center;
			}
		}
	}
	return check;
}

viewType buildView::mouseClickFunc(int state, int x, int y) {
	for (int i = 0; i < buttons.size(); i++) {
		//y is goes top to bottom for mouse,
		//and bottom to top for texture >.<
		buttons[i]->onClick(state, x, height-y);
	}
	if (state == GLUT_UP && prevMouseState != GLUT_UP) {
		if (scroll->addButton->isSelected(x, height - y) ) {
			addNode();
		}
		else if (scroll->removeButton->isSelected(x, height - y)) {
			removeNode();
		}
	}

	prevMouseState = state;

	if ((buttons[0]->isSelected(x, height - y) &&
		state == GLUT_UP)) {
		updateview = false;
		isCurrentView = false;
		return viewType::BATTLE;
	}
	else if (buttons[buttons.size() - 1]->isSelected(x, height - y)) {
		return viewType::HELP;
	}
	return viewType::BUILD;
}

void buildView::keyPressFunc(unsigned char key, int x, int y) {
	switch (key) {
	case 8: //backsapce
		//delete block
		removeNode();
		break;
	case 13: //enter
		//add block
		addNode();
		break;
	}
}

viewType buildView::checkTimeOut() {
	if (timer->timeLeft < 0) {
		return viewType::BATTLE;
	}
	return viewType::BUILD;
}

void buildView::addNode() {
	int s = NodeList.size();
	if (s < MAX_BLOCKS) {
		//screw it if it isn't valid, don't add
		Vector3 check = addNewNodePos();
		if (check.equals(center)) {
			return;
		}
		Cube * cube = new Cube(1);
		cube->localTransform.position = addNewNodePos();
		cube->identifier = s;
		PushGeoNode(cube);
		//for now, we just move the last added node
		currentNode = NodeList[NodeList.size() - 1];
	}
}

void buildView::removeNode() {
	if (NodeList.size() > 1) {
		NodeList.pop_back();
		if (NodeList.size() == 1) {
			currentNode = nullptr;  //not allowed to move base block
		}
		else {
			currentNode = NodeList[NodeList.size() - 1];
		}
	}
}

bool buildView::validPos(Vector3 t, GeoNode * node) {
	Vector3 check = node->localTransform.position + t;
	if (check.x > center.x + HALF_GRID) {
		return false;
	}
	if (check.x < center.x - HALF_GRID) {
		return false;
	}
	if (check.z > center.z + HALF_GRID) {
		return false;
	}
	if (check.z < center.z - HALF_GRID) {
		return false;
	}
	if (check.y > center.y + HALF_GRID) {
		return false;
	}
	if (check.y < center.y - HALF_GRID) {
		return false;
	}
	return true;
}

Vector3 buildView::translateNode(Vector3 t, GeoNode * node) {
	//this works for now with our small 3x3x3, until mouse raycast is implemented
	Vector3 check = node->localTransform.position + t;
	if (!validPos(t, node)) return node->localTransform.position;
	int checkBelow = check.y;
	while (checkBelow > center.y) {
		bool foundMatchBelow = false;
		for (int i = 0; i < NodeList.size(); i++) {
			Vector3 temp = NodeList[i]->localTransform.position;
			if (temp.x == check.x && temp.z == check.z) {
				if (temp.y == check.y - 1) {
					foundMatchBelow = true;
				}
			}
		}
		if (!foundMatchBelow) {
			check.y -= 1;
		}
		checkBelow--;
	}
	bool foundMatch = true;
	while (foundMatch) {
		foundMatch = false;
		for (int i = 0; i < NodeList.size(); i++) {
			Vector3 temp = NodeList[i]->localTransform.position;
			if (check.equals(temp)) {
				foundMatch = true;
				break;
			}
		}
		if (foundMatch) check.y += 1;
	}
	return check;
}