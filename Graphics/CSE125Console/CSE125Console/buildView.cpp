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
	yRotation = 0;
	rotateY.identity();
	center = Vector3(-5, -5, -5);
	static Cube * cube = new Cube(1);
	cube->localTransform.position = Vector3(0, 0, 0);
	cube->identifier = 0;
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

	//grid textures
	setTexture("uiItem/images/buildModeGrid.jpg", &grids[0]);
	setTexture("uiItem/images/blackgrid.jpg", &grids[1]);
}

void buildView::VUpdate() {
	gui::VUpdate();
	if (!updateview && isCurrentView){// || true) { //use true to disable timer
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
	//Clear color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Set the OpenGL matrix mode to ModelView
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	pViewCamera->setUpCamera();
	//glPushMatrix();
	//glLoadMatrixd(pViewCamera->GetCameraGLMatrix().getPointer());

	glPushMatrix();
	glTranslatef(center.x, center.y, center.z);
	glRotatef(yRotation, 0.0, 1.0, 0.0);

	for each (GeoNode* node in NodeList) {
		node->VOnDraw();
	};
	glPopMatrix();

	//draw grid plane quad
	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, grids[0]);
	glBegin(GL_QUADS);
	//bottom
	glTexCoord2f(0, 0); 
	glVertex3f(center.x - HALF_GRID - 0.5, center.y - 0.5, center.z - HALF_GRID - 0.5);
	glTexCoord2f(0, 1); 
	glVertex3f(center.x - HALF_GRID - 0.5, center.y - 0.5, center.z + HALF_GRID + 0.5);
	glTexCoord2f(1, 1); 
	glVertex3f(center.x + HALF_GRID + 0.5, center.y - 0.5, center.z + HALF_GRID + 0.5);
	glTexCoord2f(1, 0); 
	glVertex3f(center.x + HALF_GRID + 0.5, center.y - 0.5, center.z - HALF_GRID - 0.5);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, grids[1]);
	glBegin(GL_QUADS);
	//back
	glTexCoord2f(0, 0);
	glVertex3f(center.x - HALF_GRID - 0.5, center.y - 0.5, center.z - HALF_GRID - 0.5);
	glTexCoord2f(0, 1);
	glVertex3f(center.x - HALF_GRID - 0.5, center.y + GRID_SIZE - 0.5, center.z - HALF_GRID - 0.5);
	glTexCoord2f(1, 1);
	glVertex3f(center.x + HALF_GRID + 0.5, center.y + GRID_SIZE - 0.5, center.z - HALF_GRID - 0.5);
	glTexCoord2f(1, 0);
	glVertex3f(center.x + HALF_GRID + 0.5, center.y - 0.5, center.z - HALF_GRID - 0.5);

	//to the left
	glTexCoord2f(0, 0);
	//glNormal3f(1, 0, 0);
	glVertex3f(center.x - HALF_GRID - 0.5, center.y - 0.5, center.z - HALF_GRID - 0.5);
	glTexCoord2f(0, 1);
	//glNormal3f(1, 0, 0);
	glVertex3f(center.x - HALF_GRID - 0.5, center.y - 0.5, center.z + HALF_GRID + 0.5);
	glTexCoord2f(1, 1);
	//glNormal3f(1, 0, 0);
	glVertex3f(center.x - HALF_GRID - 0.5, center.y + GRID_SIZE - 0.5, center.z + HALF_GRID + 0.5);
	glTexCoord2f(1, 0);
	//glNormal3f(1, 0, 0);
	glVertex3f(center.x - HALF_GRID - 0.5, center.y + GRID_SIZE - 0.5, center.z - HALF_GRID - 0.5);
	glEnd();


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
				return Vector3(0,0,0);
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
		if (check.equals(Vector3(0,0,0))) {
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
	if (check.x > HALF_GRID || check.x < -HALF_GRID) {
		return false;
	}
	if (check.z > HALF_GRID || check.z < -HALF_GRID) {
		return false;
	}
	if (check.y > GRID_SIZE - 1 || check.y < 0) {
		return false;
	}
	return true;
}

Vector3 buildView::translateNode(Vector3 t, GeoNode * node) {
	//this works for now with our small 3x3x3, until mouse raycast is implemented
	//std::cout << "old: " << t.x << " " << t.y << " " << t.z << std::endl;
	//t = rotateY.transform(t);
	//std::cout << t.x << " " << t.y << " " << t.z << std::endl;
	if (yRotation == 180) {
		t.x = -t.x;
		t.z = -t.z;
	} 
	else if (yRotation == 90) {
		double temp = t.x;
		t.x = -t.z;
		t.z = temp;
	}
	else if (yRotation == 270) {
		double temp = t.x;
		t.x = t.z;
		t.z = -temp;
	}

	Vector3 check = node->localTransform.position + t;
	if (!validPos(t, node)) return node->localTransform.position;
	int checkBelow = check.y;
	while (checkBelow > 0) {
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
		if (foundMatch) {
			check.y += 1;
			t.y += 1;
		}
		if (!validPos(t, node)) {
			return node->localTransform.position;
		}
	}
	return check;
}


bool buildView::setTexture(string filename, GLuint * t) {
	*t = SOIL_load_OGL_texture
		(
		filename.c_str()
		,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	if (*t == 0)
	{
		std::cout << filename.c_str() << std::endl;
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
		return false;
	}

	//return true if successfully set texture
	//std::cout << filename << std::endl;
	//std::cout << "width: " << width << std::endl;
	//std::cout << "height: " << height << std::endl;
	return true;
}