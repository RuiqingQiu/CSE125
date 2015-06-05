#include "stdafx.h"
#include "buildView.h"
#include "Model3DFactory.h"
#include "GameCore.h"

//xcopy /y $(LocalDebuggerWorkingDirectory)\SFML-2.2\bin $(SolutionDir)\Debug

//constructors
buildView::buildView() : gui() {
	init();
	createText();
	createButtons();
}

buildView::buildView(int w, int h) : gui(w, h) {
	init();
	createText();
	createButtons();
}


buildView::~buildView() {
	gui::~gui();
}

void buildView::init() {
	pViewCamera->usePolar = true;
	show_time = true;
	//updateview = false;
	sound = new Sound();
	pViewCamera->rotation->x = 0;
	pViewCamera->position->z = -7;
	selectedType = BasicCube;
	yRotation = 180;
	//blocksLeft = MAX_BLOCKS;
	center = Vector3(0, -2, 0);
	templateSet = false;
    
    createBase();
}

void buildView::createBase() {
    //GeoNode * cube = new roboBase(3, 1);
    GeoNode * cube = Model3DFactory::generateObjectWithType(THREEBYTHREE_WOODEN);
    cube->localTransform.position = Vector3(0, 0, 0);
    cube->identifier = 0;
    cube->textureType = THREEBYTHREE_WOODEN;
    PushGeoNode(cube);
    
    GeoNode * wheel = Model3DFactory::generateObjectWithType(StoneTire);
    wheel->localTransform.position = Vector3(1.6, -0.2, 1);
    wheel->identifier = 1;
    wheel->textureType = StoneTire;
    PushGeoNode(wheel);
    
    GeoNode * wheel2 = Model3DFactory::generateObjectWithType(StoneTire);
    wheel2->localTransform.position = Vector3(-1.6, -0.2, 1);
    wheel2->identifier = 2;
    wheel2->textureType = StoneTire;
    PushGeoNode(wheel2);
    
    GeoNode * wheel3 = Model3DFactory::generateObjectWithType(StoneTire);
    wheel3->localTransform.position = Vector3(1.6, -0.2, -1);
    wheel3->identifier = 3;
    wheel3->textureType = StoneTire;
    PushGeoNode(wheel3);
    
    GeoNode * wheel4 = Model3DFactory::generateObjectWithType(StoneTire);
    wheel4->localTransform.position = Vector3(-1.6, -0.2, -1);
    wheel4->identifier = 4;
    wheel4->textureType = StoneTire;
    PushGeoNode(wheel4);
    
    setCurrentNode(false);
}

void buildView::createText() {
	//text displays
	//time.jpg dimensions: 800x100
	//"fullscreen" 1980 width ratio, 1980/2 - 200 = 740  740/1920 
	timer = new battleTimer(width*(740.0 / 1920.0), height - 60, 500, 50, false, false);
	timer->setScaling(true, false, width, height);
	//guiItems.push_back(timer);

	noMoney = new guiItem("text/money.png", width*(790.0 / 1920.0), height - 120, 400, 50, false, false);
	noMoney->setScaling(true, false, width, height);
	//guiItems.push_back(noMoney);

	//descriptions = new blockDescriptions(width - 520, 710, 500, 200, false, true);
	descriptions = new blockDescriptions(20, 100, 500, 400, true, false);
	guiItems.push_back(descriptions);

	//grid textures
	setTexture("uiItem/images/buildModeGrid.jpg", &grids[0]);
	setTexture("uiItem/images/grid_ext.png", &grids[1]);
}

void buildView::createButtons() {
	//hardcoded button sizes for now

	//battle button
	battleButton = new button("menuItem/battle.jpg", width - 220, 20, 200, 60);
	battleButton->setTexture("menuItem/battle_sel.jpg", btnState::SELECTED);
	battleButton->setTexture("menuItem/battle_press.jpg", btnState::PRESSED);
	buttons.push_back(battleButton);
	
	int scale = 4;
	
	//scroll box
	//scrollbox jpg dimensions: 1000x1200px
	scroll = new scrollBox(width - 520, 100, 0.5);
	buttons.push_back(scroll);

	//list options
	//blocks
	scroll->addListItem("blocks", ".jpg", true, true);
	scroll->addsubListItem("blocks/basic", ".jpg", BasicCube, true, false);
	scroll->addsubListItem("blocks/black", ".jpg", BLACKCUBE, true, false);
	scroll->addsubListItem("blocks/crystal", ".jpg", CrystalCube, true, false);
	scroll->addsubListItem("blocks/glowing", ".jpg", GlowingCube, true, false);
	scroll->addsubListItem("blocks/wooden", ".jpg", WoodenCube, true, false);

	scroll->addListItem("weapons", ".jpg", true, true);
	scroll->addsubListItem("weapons/bGun", ".jpg", BGun, true, false);
	scroll->addsubListItem("weapons/mace", ".jpg", Mace, true, false);
	//scroll->addsubListItem("weapons/mace2", ".jpg", ALTMACE, true, false);
	scroll->addsubListItem("weapons/mallet", ".jpg", Mallet, true, false);
	scroll->addsubListItem("weapons/needle", ".jpg", Needle, true, false);
	//scroll->addsubListItem("weapons/needle2", ".jpg", ALTNEEDLE, true, false);
	scroll->addsubListItem("weapons/railgun", ".jpg", Railgun, true, false);
	scroll->addsubListItem("weapons/turret", ".jpg", Turrent, true, false);

	//wheels
	scroll->addListItem("wheels", ".jpg", true, true);
	scroll->addsubListItem("wheels/discount", ".jpg", Discount, true, false);
	scroll->addsubListItem("wheels/stone", ".jpg", StoneTire, true, false);
	//scroll->addsubListItem("wheels/tire", ".jpg", Tire, true, false);
	scroll->addsubListItem("wheels/tire2", ".jpg", AltTire, true, false);
	scroll->addsubListItem("wheels/tron", ".jpg", TronWheel, true, false);
	scroll->addsubListItem("wheels/wooden", ".jpg", WoodenWheel, true, false);

	//bases
	scroll->addListItem("bases", ".jpg", true, true);
	scroll->addsubListItem("bases/basic", ".jpg", THREEBYTHREE_BASIC, true, false);
	scroll->addsubListItem("bases/black", ".jpg", THREEBYTHREE_BLACK, true, false);
	scroll->addsubListItem("bases/crystal", ".jpg", THREEBYTHREE_CRYSTAL, true, false);
	scroll->addsubListItem("bases/glowing", ".jpg", THREEBYTHREE_GLOWING, true, false);
	scroll->addsubListItem("bases/wooden", ".jpg", THREEBYTHREE_WOODEN, true, false);

	//templates
	scroll->addListItem("template", ".jpg", true, true);
	scroll->addsubListItem("templates/basic", ".jpg", TEMPLATE_1, true, false);
	scroll->addsubListItem("templates/black", ".jpg", TEMPLATE_4, true, false);
	scroll->addsubListItem("templates/crystal", ".jpg", TEMPLATE_5, true, false);
	scroll->addsubListItem("templates/glowing", ".jpg", TEMPLATE_2, true, false);
	scroll->addsubListItem("templates/wooden", ".jpg", TEMPLATE_3, true, false);


	//help button
	helpButton = new button("menuItem/help.png", 70, 20, 240, 60);
	helpButton->setTexture("menuItem/help_sel.png", btnState::SELECTED);
	helpButton->setTexture("menuItem/help_press.png", btnState::PRESSED);
	buttons.push_back(helpButton);
}

void buildView::VUpdate() {
	gui::VUpdate();
	timer->update();

	if (moneyFlag) {
		moneyDuration += 0.1;
	}

	if (moneyDuration >= maxDuration) {
		moneyDuration = 0;
		moneyFlag = false;
	}
}

void buildView::VOnRender() {
	GameView::highlight_first_pass();
	GameView::highlight_second_pass_build2();
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
	g_pCore->skybox->VOnDraw();
	
	for each (GeoNode* node in NodeList) {
		node->VOnDraw();
	};
	//if (currentNode->textureType == selectedType || true) 
	//	currentNode->VOnDraw();
	
	if (currentNode->textureType == selectedType) {
		GameView::highlight_first_pass_build();
		GameView::highlight_second_pass_build();
	}

	glPopMatrix();

	glPushMatrix();
	glRotatef(yRotation, 0.0, 1.0, 0.0);

	//draw grid plane quad
	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, grids[0]);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBegin(GL_QUADS);
	//bottom
	glTexCoord2f(1, 0); 
	glVertex3f(center.x - HALF_GRID - 0.5, center.y - 0.5 - (GRID_SIZE * 0.04), center.z - HALF_GRID - 0.5);
	glTexCoord2f(1, 1); 
	glVertex3f(center.x - HALF_GRID - 0.5, center.y - 0.5 - (GRID_SIZE * 0.04), center.z + HALF_GRID + 0.5);
	glTexCoord2f(0, 1); 
	glVertex3f(center.x + HALF_GRID + 0.5, center.y - 0.5 - (GRID_SIZE * 0.04), center.z + HALF_GRID + 0.5);
	glTexCoord2f(0, 0); 
	glVertex3f(center.x + HALF_GRID + 0.5, center.y - 0.5 - (GRID_SIZE * 0.04), center.z - HALF_GRID - 0.5);
	glEnd();

	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, grids[1]);
	glBegin(GL_QUADS);
	//back
	glTexCoord2f(0, 0);
	glVertex3f(center.x - HALF_GRID - 0.5, center.y - 0.5 - (GRID_SIZE * 0.04), center.z - HALF_GRID - 0.5);
	glTexCoord2f(0, 1);
	glVertex3f(center.x - HALF_GRID - 0.5, center.y + GRID_SIZE - 0.5, center.z - HALF_GRID - 0.5);
	glTexCoord2f(1, 1);
	glVertex3f(center.x + HALF_GRID + 0.5, center.y + GRID_SIZE - 0.5, center.z - HALF_GRID - 0.5);
	glTexCoord2f(1, 0);
	glVertex3f(center.x + HALF_GRID + 0.5, center.y - 0.5 - (GRID_SIZE * 0.04), center.z - HALF_GRID - 0.5);

	//to the left
	glTexCoord2f(0, 0);
	//glNormal3f(1, 0, 0);
	glVertex3f(center.x - HALF_GRID - 0.5, center.y - 0.5 - (GRID_SIZE * 0.04), center.z - HALF_GRID - 0.5);
	glTexCoord2f(0, 1);
	//glNormal3f(1, 0, 0);
	glVertex3f(center.x - HALF_GRID - 0.5, center.y - 0.5 - (GRID_SIZE * 0.04), center.z + HALF_GRID + 0.5);
	glTexCoord2f(1, 1);
	//glNormal3f(1, 0, 0);
	glVertex3f(center.x - HALF_GRID - 0.5, center.y + GRID_SIZE - 0.5, center.z + HALF_GRID + 0.5);
	glTexCoord2f(1, 0);
	//glNormal3f(1, 0, 0);
	glVertex3f(center.x - HALF_GRID - 0.5, center.y + GRID_SIZE - 0.5, center.z - HALF_GRID - 0.5);
	glEnd();


	set2d();
	drawAllItems();
	if (show_time) timer->draw();
	if (moneyFlag) noMoney->draw();
	set3d();
	
}

viewType buildView::mouseClickFunc(int state, int x, int y) {
	for (int i = 0; i < (int)buttons.size(); i++) {
		//y is goes top to bottom for mouse,
		//and bottom to top for texture >.<
		buttons[i]->onClick(state, x, height-y);
	}

    if (state == GLUT_UP && prevMouseState != GLUT_UP) {
        if (scroll->addButton->isSelected(x, height - y)) {
            // play the sound effect for selection
            cout << "buildview play sound" << endl;
            sound->playSelect();
            addNode();
        } else if (scroll->removeButton->isSelected(x, height - y)) {
            // play the sound effect for removing the object
            cout << "buildview remove play sound" << endl;
            sound->playSelect();
            removeNode();
        } else if (scroll->clearButton->isSelected(x, height - y)) {
            while ((int)NodeList.size() > 0) { //BASE_SIZE) {  //for resetting completely, return all money
                //std::cout << "removing" << std::endl;
                removeNode();
            }
            createBase();
        }
    }

	if (selectedType != scroll->currentSelection ) {
		selectedType = scroll->currentSelection;
		descriptions->currDescription = selectedType;
		setTemplate();
	}

	setCurrentNode(false);
	prevMouseState = state;

	if ((battleButton->isSelected(x, height - y) &&
		state == GLUT_UP)) {
		//updateview = false;
		isCurrentView = false;
		return viewType::BATTLE;
	}
	else if (helpButton->isSelected(x, height - y)) {
		return viewType::HELP;
	}
	return viewType::BUILD;
}

void buildView::keyPressFunc(unsigned char key, int x, int y) {
	switch (key) {
	case 8: //backsapce
		//delete block
		sound->playSelect();  // play the selection sound
		removeNode();
		break;
	case 13: //enter
		//add block
		sound->playSelect(); // play the seletion sound 
		addNode();
		break;
	}
}

void buildView::setConstraints() {
	clearConstraints();
	for (int i = 0; i < (int)NodeList.size(); i++) {
		Vector3 compare = NodeList[i]->localTransform.position;
		for (int j = 0; j < (int)NodeList.size(); j++) {
			Vector3 check = NodeList[j]->localTransform.position;
			if (NodeList[i]->identifier != NodeList[j]->identifier) {
				Vector3 translate = compare;
				translate.y -= 1;
				if (NodeList[j]->intersect(translate)) {
					NodeList[i]->below_id = NodeList[j]->identifier;
				}
				else {
					translate = compare;
					translate.z -= 1;
					if (NodeList[j]->intersect(translate)) {
						NodeList[i]->back_id = NodeList[j]->identifier;
					}
					else {
						translate.z += 2;
						if (NodeList[j]->intersect(translate)) {
							NodeList[i]->front_id = NodeList[j]->identifier;
						}
						else {
							translate = compare;
							translate.x -= 1;
							if (NodeList[j]->intersect(translate)) {
								NodeList[i]->left_id = NodeList[j]->identifier;
							}
							else {
								translate.x += 2;
								if (NodeList[j]->intersect(translate)) {
									NodeList[i]->right_id = NodeList[j]->identifier;
								}
							}
						}
					}
				}
			}
		}
	}
}

void buildView::clearConstraints() {
	for (int i = 0; i < (int)NodeList.size(); i++) {
		NodeList[i]->clearConstraints();
	}
}

void buildView::setCurrentNode(bool adding) {
	int type = selectedType;

	if (selectedType >= WHEEL_BEGIN && selectedType <= WHEEL_END) {
		type = BasicCube;
	}
	if (selectedType >= BASES_BEGIN && selectedType <= BASES_END) {
		type = BasicCube;
	}
	if (selectedType >= TEMPLATE_BEGIN && selectedType <= TEMPLATE_END) {
		type = BasicCube;
	}

	Model3D * object = Model3DFactory::generateObjectWithType(type);
	object->localTransform.position = addNewNodePos();
	object->identifier = (int)NodeList.size();
	object->textureType = type;
	object->setShaderType(EDGE_SHADER);

	if (!adding) delete currentNode;
	currentNode = object;
}

void buildView::setTemplate() {
	//if template, base or wheel is clicked 
	//add imediately instead of waiting for add button click or enter key press
	if (selectedType >= TEMPLATE_BEGIN && selectedType <= TEMPLATE_END) {

		//add the selected template robot build
		if (selectedType == TEMPLATE_1) {
			int templateCost = 188;
			if (startingMoney - templateCost < 0) {
				moneyFlag = true;
				return;
			}
			clearNodes();
			money = startingMoney - templateCost;
			//robo base
			GeoNode * cube = Model3DFactory::generateObjectWithType(THREEBYTHREE_BASIC);
			cube->localTransform.position = Vector3(0, 0, 0);
			cube->identifier = 0;
			cube->textureType = THREEBYTHREE_BASIC;
			PushGeoNode(cube);
			GeoNode * wheel = Model3DFactory::generateObjectWithType(Discount);
			wheel->localTransform.position = Vector3(1.6, -0.2, 1);
			wheel->identifier = 1;
			wheel->textureType = Discount;
			PushGeoNode(wheel);
			GeoNode * wheel2 = Model3DFactory::generateObjectWithType(Discount);
			wheel2->localTransform.position = Vector3(-1.6, -0.2, 1);
			wheel2->identifier = 2;
			wheel2->textureType = Discount;
			PushGeoNode(wheel2);
			GeoNode * wheel3 = Model3DFactory::generateObjectWithType(Discount);
			wheel3->localTransform.position = Vector3(1.6, -0.2, -1);
			wheel3->identifier = 3;
			wheel3->textureType = Discount;
			PushGeoNode(wheel3);
			GeoNode * wheel4 = Model3DFactory::generateObjectWithType(Discount);
			wheel4->localTransform.position = Vector3(-1.6, -0.2, -1);
			wheel4->identifier = 4;
			wheel4->textureType = Discount;
			PushGeoNode(wheel4);

			//added stuff to robot
			GeoNode * cube1 = Model3DFactory::generateObjectWithType(BasicCube);
			cube1->localTransform.position = Vector3(-1, 1, -1);
			cube1->identifier = (int)NodeList.size();
			cube1->textureType = BasicCube;
			PushGeoNode(cube1);
			GeoNode * cube2 = Model3DFactory::generateObjectWithType(BasicCube);
			cube2->localTransform.position = Vector3(1, 1, -1);
			cube2->identifier = (int)NodeList.size();
			cube2->textureType = BasicCube;
			PushGeoNode(cube2);
			GeoNode * cube3 = Model3DFactory::generateObjectWithType(BasicCube);
			cube3->localTransform.position = Vector3(-1, 1, 1);
			cube3->identifier = (int)NodeList.size();
			cube3->textureType = BasicCube;
			PushGeoNode(cube3);
			GeoNode * cube4 = Model3DFactory::generateObjectWithType(BasicCube);
			cube4->localTransform.position = Vector3(1, 1, 1);
			cube4->identifier = (int)NodeList.size();
			cube4->textureType = BasicCube;
			PushGeoNode(cube4);

			GeoNode * weapon1 = Model3DFactory::generateObjectWithType(Needle);
			weapon1->localTransform.position = Vector3(-1, 0, -2);
			weapon1->identifier = (int)NodeList.size();
			weapon1->textureType = Needle;
			PushGeoNode(weapon1);
			GeoNode * weapon2 = Model3DFactory::generateObjectWithType(Needle);
			weapon2->localTransform.position = Vector3(-1, 1, -2);
			weapon2->identifier = (int)NodeList.size();
			weapon2->textureType = Needle;
			PushGeoNode(weapon2);
			GeoNode * weapon3 = Model3DFactory::generateObjectWithType(Needle);
			weapon3->localTransform.position = Vector3(1, 0, -2);
			weapon3->identifier = (int)NodeList.size();
			weapon3->textureType = Needle;
			PushGeoNode(weapon3);
			GeoNode * weapon4 = Model3DFactory::generateObjectWithType(Needle);
			weapon4->localTransform.position = Vector3(1, 1, -2);
			weapon4->identifier = (int)NodeList.size();
			weapon4->textureType = Needle;
			PushGeoNode(weapon4);
		}
		else if (selectedType == TEMPLATE_2) {
			int templateCost = 330;
			if (startingMoney - templateCost < 0) {
				moneyFlag = true;
				return;
			}
			clearNodes();
			money = startingMoney - templateCost;
			//robo base
			GeoNode * cube = Model3DFactory::generateObjectWithType(THREEBYTHREE_GLOWING);
			cube->localTransform.position = Vector3(0, 0, 0);
			cube->identifier = 0;
			cube->textureType = THREEBYTHREE_GLOWING;
			PushGeoNode(cube);
			GeoNode * wheel = Model3DFactory::generateObjectWithType(AltTire);
			wheel->localTransform.position = Vector3(1.6, -0.2, 1);
			wheel->identifier = 1;
			wheel->textureType = AltTire;
			PushGeoNode(wheel);
			GeoNode * wheel2 = Model3DFactory::generateObjectWithType(AltTire);
			wheel2->localTransform.position = Vector3(-1.6, -0.2, 1);
			wheel2->identifier = 2;
			wheel2->textureType = AltTire;
			PushGeoNode(wheel2);
			GeoNode * wheel3 = Model3DFactory::generateObjectWithType(AltTire);
			wheel3->localTransform.position = Vector3(1.6, -0.2, -1);
			wheel3->identifier = 3;
			wheel3->textureType = AltTire;
			PushGeoNode(wheel3);
			GeoNode * wheel4 = Model3DFactory::generateObjectWithType(AltTire);
			wheel4->localTransform.position = Vector3(-1.6, -0.2, -1);
			wheel4->identifier = 4;
			wheel4->textureType = AltTire;
			PushGeoNode(wheel4);

			//added stuff to robot
			GeoNode * cube2 = Model3DFactory::generateObjectWithType(GlowingCube);
			cube2->localTransform.position = Vector3(0, 1, 0);
			cube2->identifier = (int)NodeList.size();
			cube2->textureType = GlowingCube;
			PushGeoNode(cube2);

			GeoNode * weapon1 = Model3DFactory::generateObjectWithType(Railgun);
			weapon1->localTransform.position = Vector3(0, 1, -1);
			weapon1->identifier = (int)NodeList.size();
			weapon1->textureType = Needle;
			PushGeoNode(weapon1);
			GeoNode * weapon2 = Model3DFactory::generateObjectWithType(Railgun);
			weapon2->localTransform.position = Vector3(0, 1, 1);
			weapon2->localTransform.rotation.y = 180;
			weapon2->identifier = (int)NodeList.size();
			weapon2->textureType = Mallet;
			PushGeoNode(weapon2);
			GeoNode * weapon3 = Model3DFactory::generateObjectWithType(BGun);
			weapon3->localTransform.position = Vector3(-1, 1, 0);
			weapon3->localTransform.rotation.y = 90;
			weapon3->identifier = (int)NodeList.size();
			weapon3->textureType = Needle;
			PushGeoNode(weapon3);
			GeoNode * weapon4 = Model3DFactory::generateObjectWithType(BGun);
			weapon4->localTransform.position = Vector3(1, 1, 0);
			weapon4->localTransform.rotation.y = 270;
			weapon4->identifier = (int)NodeList.size();
			weapon4->textureType = Mallet;
			PushGeoNode(weapon4);
		}
		else if (selectedType == TEMPLATE_3) {
			int templateCost = 66;
			if (startingMoney - templateCost < 0) {
				moneyFlag = true;
				return;
			}
			clearNodes();
			money = startingMoney - templateCost;
			//robo base
			GeoNode * cube = Model3DFactory::generateObjectWithType(THREEBYTHREE_WOODEN);
			cube->localTransform.position = Vector3(0, 0, 0);
			cube->identifier = 0;
			cube->textureType = THREEBYTHREE_WOODEN;
			PushGeoNode(cube);
			GeoNode * wheel = Model3DFactory::generateObjectWithType(WoodenWheel);
			wheel->localTransform.position = Vector3(1.6, -0.2, 1);
			wheel->identifier = 1;
			wheel->textureType = WoodenWheel;
			PushGeoNode(wheel);
			GeoNode * wheel2 = Model3DFactory::generateObjectWithType(WoodenWheel);
			wheel2->localTransform.position = Vector3(-1.6, -0.2, 1);
			wheel2->identifier = 2;
			wheel2->textureType = WoodenWheel;
			PushGeoNode(wheel2);
			GeoNode * wheel3 = Model3DFactory::generateObjectWithType(WoodenWheel);
			wheel3->localTransform.position = Vector3(1.6, -0.2, -1);
			wheel3->identifier = 3;
			wheel3->textureType = WoodenWheel;
			PushGeoNode(wheel3);
			GeoNode * wheel4 = Model3DFactory::generateObjectWithType(WoodenWheel);
			wheel4->localTransform.position = Vector3(-1.6, -0.2, -1);
			wheel4->identifier = 4;
			wheel4->textureType = WoodenWheel;
			PushGeoNode(wheel4);

			//added stuff to robot
			GeoNode * cube1 = Model3DFactory::generateObjectWithType(WoodenCube);
			cube1->localTransform.position = Vector3(1, 1, -1);
			cube1->identifier = (int)NodeList.size();
			cube1->textureType = WoodenCube;
			PushGeoNode(cube1);
			GeoNode * cube2 = Model3DFactory::generateObjectWithType(WoodenCube);
			cube2->localTransform.position = Vector3(-1, 1, -1);
			cube2->identifier = (int)NodeList.size();
			cube2->textureType = WoodenCube;
			PushGeoNode(cube2);
			GeoNode * cube3 = Model3DFactory::generateObjectWithType(WoodenCube);
			cube3->localTransform.position = Vector3(0, 1, -1);
			cube3->identifier = (int)NodeList.size();
			cube3->textureType = WoodenCube;
			PushGeoNode(cube3);
			GeoNode * cube4 = Model3DFactory::generateObjectWithType(WoodenCube);
			cube4->localTransform.position = Vector3(0, 2, 1);
			cube4->identifier = (int)NodeList.size();
			cube4->textureType = WoodenCube;
			PushGeoNode(cube4);
			GeoNode * cube5 = Model3DFactory::generateObjectWithType(WoodenCube);
			cube5->localTransform.position = Vector3(0, 1, 0);
			cube5->identifier = (int)NodeList.size();
			cube5->textureType = WoodenCube;
			PushGeoNode(cube5);
			GeoNode * cube6 = Model3DFactory::generateObjectWithType(WoodenCube);
			cube6->localTransform.position = Vector3(0, 2, 0);
			cube6->identifier = (int)NodeList.size();
			cube6->textureType = WoodenCube;
			PushGeoNode(cube6);
			GeoNode * cube7 = Model3DFactory::generateObjectWithType(WoodenCube);
			cube7->localTransform.position = Vector3(0, 1, 1);
			cube7->identifier = (int)NodeList.size();
			cube7->textureType = WoodenCube;
			PushGeoNode(cube7);

			GeoNode * weapon1 = Model3DFactory::generateObjectWithType(Needle);
			weapon1->localTransform.position = Vector3(0, 0, -2);
			weapon1->identifier = (int)NodeList.size();
			weapon1->textureType = Needle;
			PushGeoNode(weapon1);
			GeoNode * weapon2 = Model3DFactory::generateObjectWithType(Needle);
			weapon2->localTransform.position = Vector3(1, 0, -2);
			weapon2->identifier = (int)NodeList.size();
			weapon2->textureType = Needle;
			PushGeoNode(weapon2);
			GeoNode * weapon3 = Model3DFactory::generateObjectWithType(Needle);
			weapon3->localTransform.position = Vector3(-1, 0, -2);
			weapon3->identifier = (int)NodeList.size();
			weapon3->textureType = Needle;
			PushGeoNode(weapon3);
			GeoNode * weapon4 = Model3DFactory::generateObjectWithType(Mace);
			weapon4->localTransform.position = Vector3(0, 1, -2);
			weapon4->identifier = (int)NodeList.size();
			weapon4->textureType = Mace;
			PushGeoNode(weapon4);

		}
		else if (selectedType == TEMPLATE_4) {
			int templateCost = 312;
			if (startingMoney - templateCost < 0) {
				moneyFlag = true;
				return;
			}
			clearNodes();
			money = startingMoney - templateCost;
			//robo base
			GeoNode * cube = Model3DFactory::generateObjectWithType(THREEBYTHREE_BLACK);
			cube->localTransform.position = Vector3(0, 0, 0);
			cube->identifier = 0;
			cube->textureType = THREEBYTHREE_BLACK;
			PushGeoNode(cube);
			GeoNode * wheel = Model3DFactory::generateObjectWithType(TronWheel);
			wheel->localTransform.position = Vector3(1.6, -0.2, 1);
			wheel->identifier = 1;
			wheel->textureType = TronWheel;
			PushGeoNode(wheel);
			GeoNode * wheel2 = Model3DFactory::generateObjectWithType(TronWheel);
			wheel2->localTransform.position = Vector3(-1.6, -0.2, 1);
			wheel2->identifier = 2;
			wheel2->textureType = TronWheel;
			PushGeoNode(wheel2);
			GeoNode * wheel3 = Model3DFactory::generateObjectWithType(TronWheel);
			wheel3->localTransform.position = Vector3(1.6, -0.2, -1);
			wheel3->identifier = 3;
			wheel3->textureType = TronWheel;
			PushGeoNode(wheel3);
			GeoNode * wheel4 = Model3DFactory::generateObjectWithType(TronWheel);
			wheel4->localTransform.position = Vector3(-1.6, -0.2, -1);
			wheel4->identifier = 4;
			wheel4->textureType = TronWheel;
			PushGeoNode(wheel4);

			//added stuff to robot
			GeoNode * cube1 = Model3DFactory::generateObjectWithType(BLACKCUBE);
			cube1->localTransform.position = Vector3(-1, 1, 1);
			cube1->identifier = (int)NodeList.size();
			cube1->textureType = BLACKCUBE;
			PushGeoNode(cube1);
			GeoNode * cube2 = Model3DFactory::generateObjectWithType(BLACKCUBE);
			cube2->localTransform.position = Vector3(1, 1, 1);
			cube2->identifier = (int)NodeList.size();
			cube2->textureType = BLACKCUBE;
			PushGeoNode(cube2);
			GeoNode * weapon1 = Model3DFactory::generateObjectWithType(Needle);
			weapon1->localTransform.position = Vector3(0, 0, -2);
			weapon1->identifier = (int)NodeList.size();
			weapon1->textureType = Needle;
			PushGeoNode(weapon1);
			GeoNode * weapon2 = Model3DFactory::generateObjectWithType(Needle);
			weapon2->localTransform.position = Vector3(1, 0, -2);
			weapon2->identifier = (int)NodeList.size();
			weapon2->textureType = Railgun;
			PushGeoNode(weapon2);
			GeoNode * weapon3 = Model3DFactory::generateObjectWithType(Needle);
			weapon3->localTransform.position = Vector3(-1, 0, -2);
			weapon3->identifier = (int)NodeList.size();
			weapon3->textureType = Railgun;
			PushGeoNode(weapon3);
			GeoNode * weapon4 = Model3DFactory::generateObjectWithType(Needle);
			weapon4->localTransform.position = Vector3(0, 0, 2);
			weapon4->localTransform.rotation.y = 180;
			weapon4->identifier = (int)NodeList.size();
			weapon4->textureType = Needle;
			PushGeoNode(weapon4);
			GeoNode * weapon5 = Model3DFactory::generateObjectWithType(Needle);
			weapon5->localTransform.position = Vector3(1, 0, 2);
			weapon5->localTransform.rotation.y = 180;
			weapon5->identifier = (int)NodeList.size();
			weapon5->textureType = Railgun;
			PushGeoNode(weapon5);
			GeoNode * weapon6 = Model3DFactory::generateObjectWithType(Needle);
			weapon6->localTransform.position = Vector3(-1, 0, 2);
			weapon6->localTransform.rotation.y = 180;
			weapon6->identifier = (int)NodeList.size();
			weapon6->textureType = Railgun;
			PushGeoNode(weapon6);
		}
		else {
			int templateCost = 260;
			if (startingMoney - templateCost < 0) {
				moneyFlag = true;
				return;
			}
			clearNodes();
			money = startingMoney - templateCost;
			//robo base
			GeoNode * cube = Model3DFactory::generateObjectWithType(THREEBYTHREE_CRYSTAL);
			cube->localTransform.position = Vector3(0, 0, 0);
			cube->identifier = 0;
			cube->textureType = THREEBYTHREE_CRYSTAL;
			PushGeoNode(cube);
			GeoNode * wheel = Model3DFactory::generateObjectWithType(StoneTire);
			wheel->localTransform.position = Vector3(1.6, -0.2, 1);
			wheel->identifier = 1;
			wheel->textureType = StoneTire;
			PushGeoNode(wheel);
			GeoNode * wheel2 = Model3DFactory::generateObjectWithType(StoneTire);
			wheel2->localTransform.position = Vector3(-1.6, -0.2, 1);
			wheel2->identifier = 2;
			wheel2->textureType = StoneTire;
			PushGeoNode(wheel2);
			GeoNode * wheel3 = Model3DFactory::generateObjectWithType(StoneTire);
			wheel3->localTransform.position = Vector3(1.6, -0.2, -1);
			wheel3->identifier = 3;
			wheel3->textureType = StoneTire;
			PushGeoNode(wheel3);
			GeoNode * wheel4 = Model3DFactory::generateObjectWithType(StoneTire);
			wheel4->localTransform.position = Vector3(-1.6, -0.2, -1);
			wheel4->identifier = 4;
			wheel4->textureType = StoneTire;
			PushGeoNode(wheel4);

			//added stuff to robot
			GeoNode * cube1 = Model3DFactory::generateObjectWithType(CrystalCube);
			cube1->localTransform.position = Vector3(-1, 1, 1);
			cube1->identifier = (int)NodeList.size();
			cube1->textureType = CrystalCube;
			PushGeoNode(cube1);
			GeoNode * cube2 = Model3DFactory::generateObjectWithType(CrystalCube);
			cube2->localTransform.position = Vector3(1, 1, 1);
			cube2->identifier = (int)NodeList.size();
			cube2->textureType = CrystalCube;
			PushGeoNode(cube2);
			GeoNode * cube3 = Model3DFactory::generateObjectWithType(CrystalCube);
			cube3->localTransform.position = Vector3(-1, 2, 1);
			cube3->identifier = (int)NodeList.size();
			cube3->textureType = CrystalCube;
			PushGeoNode(cube3);
			GeoNode * cube4 = Model3DFactory::generateObjectWithType(CrystalCube);
			cube4->localTransform.position = Vector3(1, 2, 1);
			cube4->identifier = (int)NodeList.size();
			cube4->textureType = CrystalCube;
			PushGeoNode(cube4);

			GeoNode * weapon1 = Model3DFactory::generateObjectWithType(Mace);
			weapon1->localTransform.position = Vector3(0, 0, -2);
			weapon1->identifier = (int)NodeList.size();
			weapon1->textureType = ALTMACE;
			PushGeoNode(weapon1);
			GeoNode * weapon2 = Model3DFactory::generateObjectWithType(Turrent);
			weapon2->localTransform.position = Vector3(-1, 0, -2);
			weapon2->identifier = (int)NodeList.size();
			weapon2->textureType = Railgun;
			PushGeoNode(weapon2);
			GeoNode * weapon3 = Model3DFactory::generateObjectWithType(Turrent);
			weapon3->localTransform.position = Vector3(1, 0, -2);
			weapon3->identifier = (int)NodeList.size();
			weapon3->textureType = Railgun;
			PushGeoNode(weapon3);
		}

		setConstraints();
		return;
	}

	if (selectedType >= BASES_BEGIN && selectedType <= BASES_END) {
		GeoNode * cube = Model3DFactory::generateObjectWithType(selectedType);
		cube->localTransform.position = Vector3(0, 0, 0);
		cube->identifier = 0;
		cube->textureType = selectedType;
		
		money += NodeList[0]->cost;
		if (money - cube->cost < 0) {
			moneyFlag = true;
			money -= NodeList[0]->cost;
			return;
		}

		delete NodeList[0];
		NodeList[0] = cube;
		money -= NodeList[0]->cost;
		return;
	}

	if (selectedType >= WHEEL_BEGIN && selectedType <= WHEEL_END) {
		//is a wheel
		GeoNode * object = Model3DFactory::generateObjectWithType(selectedType);
		money += NodeList[1]->cost;
		if (money - object->cost < 0) {
			moneyFlag = true;
			money -= NodeList[1]->cost;
			return;
		}
		for (int i = 1; i < BASE_SIZE; i++) {
			object = Model3DFactory::generateObjectWithType(selectedType);
			object->localTransform.position = NodeList[i]->localTransform.position;
			object->identifier = NodeList[i]->identifier;
			object->textureType = selectedType;
			delete NodeList[i];
			NodeList[i] = object;
		}
		money -= NodeList[1]->cost;
		return;
	}
}


Vector3 buildView::addNewNodePos() {
	//for now, just add to the right of current node
	//logic here for finding place to start new node
	Vector3 check;

	if (currentNode == nullptr)
		check = translateNode(Vector3(0, 1, 0), NodeList[0]);
	else
		check = translateNode(Vector3(1, 0, 0), currentNode);

	if (currentNode != nullptr) {
		Vector3 temp = currentNode->localTransform.position;
		//if we got same position, try to the left
		if (check.equals(temp)) {
			check = translateNode(Vector3(-1, 0, 0), currentNode);
			//if still invalid, fuck it just don't add a new node
			if (check.equals(temp)) {
				return Vector3(0, 0, 0);
			}
		}
	}
	return check;
}

void buildView::addNode() {
	if (currentNode->textureType != selectedType) return;
	if ((int)NodeList.size() < MAX_BLOCKS) {
		//screw it if it isn't valid, don't add
		Vector3 check = addNewNodePos();
		if (check.equals(Vector3(0, 0, 0))) {
			return;
		}
		if (money - currentNode->cost < 0) {
			moneyFlag = true;
			return;
		}
		currentNode->setShaderType(NORMAL_SHADER);
		PushGeoNode(currentNode);
		money -= currentNode->cost;
		//currentNode = NodeList[NodeList.size() - 1];
		setCurrentNode(true);
		setConstraints();
	}
}

void buildView::clearNodes() {
	for (int i = 0; i < (int) NodeList.size(); i++) {
		money += NodeList[i]->cost;
		delete NodeList[i];
	}
	NodeList.clear();
}

void buildView::removeNode() {
	//if ((int) NodeList.size() > BASE_SIZE) {
		money += NodeList[NodeList.size() - 1]->cost;
		delete NodeList[NodeList.size() - 1];
		NodeList.pop_back();
	//}
	setCurrentNode(false);
}

bool buildView::validPos(Vector3 t, GeoNode * node) {
	Vector3 check = node->localTransform.position + t;
	if (check.x > HALF_GRID - 1 || check.x < -HALF_GRID + 1) {
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
		for (int i = 0; i < (int)NodeList.size(); i++) {
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
		for (int i = 0; i < (int)NodeList.size(); i++) {
			Vector3 temp = NodeList[i]->localTransform.position;
			if (NodeList[i]->intersect(check)) {
				node->below_id = NodeList[i]->identifier;
				foundMatch = true;
				break;
			}
		}
		if (foundMatch) {
			check.y += 1;
			t.y += 1;
		}
		if (!validPos(t, node)) {
			setConstraints();
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
	return true;
}

void buildView::rotateRobot(float degrees) {
	yRotation += degrees;

	//keep it in the range 0 - 360
	if (yRotation < 0) yRotation += 360;
	if (yRotation >= 360) yRotation -= 360;
}