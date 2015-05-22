#include "stdafx.h"
#include "mainmenu.h"
#include <iostream>
#include <string>

int span = 20; // the space between each letter
int start_w; // start to display robot name
int start_h; // height should be the same

mainMenu::mainMenu() : gui() {
	w = width;
	h = height;
	playerReady = 0;
	ready = false;
	displayName = 0; // default doesn't display name or ip address
	displayIp = 0;
	start_w = w * 0.5;
	start_h = h * 0.53; 
	letterOffset = 0.0;
	createButtons();
}

mainMenu::mainMenu(int w, int h) : gui(w, h) {
	w = width;
	h = height;
	ready = false;
	playerReady = 0;
	start_w = w * 0.5;
	start_h = h * 0.53;
	letterOffset = 0.0;
	createButtons();
}

mainMenu::~mainMenu(){

}

void mainMenu::createButtons() {
	isLoading = true;
	playPressed = false;

	button * robo = new button("menuItem/enterRobotName.jpg", width*0.3, height*0.5, 750, 100);
	robo->setScaling(true, true, width, height);

	//set up enter IP button
	ipAdrressButton = new button("menuItem/enterIP.jpg", width*0.3, height*0.4, 750, 100);
	ipAdrressButton->setScaling(true, true, width, height);
	
	playButton = new button("menuItem/play.jpg", width*0.43, height*0.3, 260, 50);
	playButton->setTexture("menuItem/play_sel.jpg", btnState::SELECTED);
	playButton->setTexture("menuItem/play_press.jpg", btnState::PRESSED);
	playButton->setScaling(true, true, width, height);

	helpButton = new button("menuItem/help.jpg", width*0.43, height * 0.2, 260, 50);
	helpButton->setTexture("menuItem/help_sel.jpg", btnState::SELECTED);
	helpButton->setTexture("menuItem/help_press.jpg", btnState::PRESSED);
	helpButton->setScaling(true, true, width, height);

	exitButton = new button("menuItem/exit.jpg", width*0.43, height * 0.1, 260, 50);
	exitButton->setTexture("menuItem/exit_sel.jpg", btnState::SELECTED);
	exitButton->setTexture("menuItem/exit_press.jpg", btnState::PRESSED);
	exitButton->setScaling(true, true, width, height);

	buttons.push_back(robo);// button[0] is robot name
	buttons.push_back(playButton);
	buttons.push_back(helpButton);
	buttons.push_back(exitButton);
	buttons.push_back(ipAdrressButton); // button[4] is enterIP Address

	// the loading view after click on play button
	loading = new loadDisplay(width*0.43, height*0.3, 250, 250);

	backimg = new background("background1.jpg", width, height);
	guiItems.push_back(backimg); // push in to the guiTexts vector
	playersReady = new numDisplay("text/playersReady.jpg", width*(760.0 / 1920.0), height - 150, 400, 50,1); 
	
}

// overwrite the gui drawAllItems function
void mainMenu::drawAllItems(){
	// but need to draw background first
	guiItems[0]->draw();

	// if player cliced on play button
	if (playPressed) {
		loading->draw(); // draw the loading view
		playersReady->draw();  // draw the number of player ready
	}
	else {
		// exchange the order, draw button first and then draw guiItems 
		for (int i = 0; i < buttons.size(); i++) {
			buttons[i]->draw();
		}
		for (int i = 1; i < guiItems.size(); i++) {
			guiItems[i]->draw();
		}
	}
}

void mainMenu::VUpdate() {
	gui::VUpdate();
	loading->update();
	playersReady->displayValue = playerReady; // update the player ready value
	playersReady->update(); // update number display
}

// add letters to the guiItem array
void mainMenu::addLetters(){
	w = width;
	h = height;
	start_w = width * 0.5;
	start_h = h * 0.54;
	letterOffset = (buttons[0]->getYPos() + buttons[0]->getHeight()) - ((buttons[0]->getHeight() - 22) / 2) - 24.5; // offset fits now
	int counter = 0;
	// clear the guiNumbers and guiLetters
	guiNumbers.clear();
	guiLetters.clear();

	if (displayName == 1){
		// set the gamecore player name at the mainmenuinput file
		string n = g_pCore->i_pInput->name; // get the name of game core
		//guiLetters.clear(); // clear the guiLetters every time and start over
		counter = 0;
		// loop through the string
		for (string::iterator it = n.begin(); it != n.end(); ++it) {
			if (int(*it) != 32) {
				letters *l = new letters(start_w + counter * span, letterOffset, 22, 21.5); // pass in x,y position and its size
				l->letterToShow = int(*it) - 97; // from char to array index
				guiLetters.push_back(l);
			}
			counter++;
		}
	}

	if (displayIp == 1){
		string address = g_pCore->i_pInput->IPAdress;
		//guiNumbers.clear();
		letterOffset = (buttons[4]->getYPos() + buttons[4]->getHeight()) - ((buttons[4]->getHeight() - 22) / 2) - 24.5; // offset for ip displaying
		// loop through the ipAdress string
		counter = 0;
		for (string::iterator it = address.begin(); it != address.end(); ++it) {
			// dot is 46, if it is dot 
			if (int(*it) - 46 == 0){
				// default path of guiItem is uiItem
				// cannot assume the IP address format is always the same
				//dotPosition.push(counter); // the position of the dot in the actual ip address
				guiItem* dot = new guiItem("text/symbols/dot.jpg", start_w + counter * span, letterOffset, 22, 21.5);
				guiNumbers.push_back(dot);
				counter++;
				continue;
			}
			numbers *num = new numbers(start_w + counter * span, letterOffset, 22, 21.5); // pass in x,y position and its size
			num->numIdx = int(*it) - 48; // from char to array index
			guiNumbers.push_back(num);
			counter++;
		}
	}

	// Deletes the 2nd through 3rd elements (vec[1], vec[2])
	//guiItems.erase(guiItems.begin() + 1, guiItems.begin() + guiItems.size);
	guiItems.clear(); // clear the guiItem to avoid adding elements all more than once
	guiItems.push_back(backimg); // backimg render first every time


	// if display Ip selected
	if (displayIp){
		// after push back the robot names, push back the ip address
		for (std::vector<guiItem*> ::iterator it = guiNumbers.begin(); it != guiNumbers.end(); ++it){
			guiItems.push_back(*it);
		}
	}

	// if enter Robot name selected
	if (displayName){
		for (std::vector<guiItem*> ::iterator it = guiLetters.begin(); it != guiLetters.end(); ++it){
			guiItems.push_back(*it);
		}
	}
}

void mainMenu::VOnRender() {
	GameView::VOnRender();
	set2d();
	addLetters();
	drawAllItems();

	// draw how many players are ready, drawText defined in gui.cpp
	//drawText(width*(760.0 / 1920.0), height - 150, std::to_string(playerReady) + " / " + std::to_string(MAX_PLAYER) + " players are ready", 1.0, 1.0, 1.0, GLUT_BITMAP_HELVETICA_18);
	set3d();
}

void mainMenu::VOnClientUpdate(GameInfoPacket* info) {

}


viewType mainMenu::mouseClickFunc(int state, int x, int y){
	if (playPressed && isLoading) return viewType::MENU;
	if (playPressed && !isLoading) return viewType::BUILD;
	for (int i = 0; i < buttons.size(); i++) {
		//y is goes top to bottom for mouse,
		//and bottom to top for texture >.<
		buttons[i]->onClick(state, x, height - y);
	}

	if (state != GLUT_UP) return viewType::MENU;
	

	// if enter IP address is selected
	if (ipAdrressButton->isSelected(x, height - y)){
		displayIp = true;
	}

	// if enter robot name is selected
	if (buttons[0]->isSelected(x, height - y)){
		displayName = true;
	}

	//play button
	if (playButton->isSelected(x, height - y)) {
		playPressed = true;
		if (!ready){
			ready = true;
			// if hit play button, means is ready
			g_pCore->pGamePacketManager->ConnectToServer((char*)(g_pCore->pPlayer->IPAddress.c_str()));
			playerReady = playerReady + 1;
		}
		// if all the players are ready, go to the build view
		if (playerReady == MAX_PLAYER)
			return viewType::BUILD;
	}
	// help button
	else if (helpButton->isSelected(x, height - y)){
		return viewType::HELP;
	}
	else if (exitButton->isSelected(x, height - y)) {
		exit(0);
	}	
	// stay at the menu button
	return viewType::MENU;
}