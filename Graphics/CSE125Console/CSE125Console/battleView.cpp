#include "stdafx.h"
#include "battleView.h"

battleView::battleView(): gui(){
	createButtons();
	GameView::GameView();
}

battleView::battleView(int w, int h) : gui(w, h) {
	createButtons();
	GameView::GameView();
}

battleView::~battleView()
{
}

// create all the buttons on the battle view
void battleView:: createButtons() {
	// display the time left
	timer = new battleTimer(width*0.3, height - 50, 500, 50, false, false);
	timer->setScaling(true, false, width, height);
	guiItems.push_back(timer);

	healthDisplay = new healthBar(10, 10, 650, 100, true, false);
	guiItems.push_back(healthDisplay);

	takeDamage = new background("TakeDamage.png", width, height);
	onDeath = new guiItem("HUD/dead.png", width*0.5 - 500, height* 0.7, 1000, 200, false, false);
	onDeath->setScaling(true, false, width, height);

	//cooldown = new cooldownDisplay(100, 100, 250, 250, true, false);
	//guiItems.push_back(cooldown);
}

void battleView::VUpdate() {
	gui::VUpdate();

	if (!updateview && isCurrentView){
		//timer->start = std::clock();
	}
	updateview = isCurrentView;

	if (damageTaken || currDuration > 0) {
		currDuration += 0.1;
	}

	if (currDuration == maxDuration) {
		currDuration = 0;
	}

	if (damageTaken) damageTaken = false;
}

void battleView::updateName(string name) {
	healthDisplay->updateRobotName(name);
}

	
void battleView::VOnRender() {
	GameView::VOnRender();
	set2d();

	//glEnable(GL_COLOR_MATERIAL);
	//glColor4f(1.0, 1.0, 1.0, 1.0 - (currDuration / maxDuration) );
	if (damageTaken || isDead) takeDamage->draw();
	if (isDead) onDeath->draw();
	//glDisable(GL_COLOR_MATERIAL);

	drawAllItems();
	set3d();
}

viewType battleView::mouseClickFunc(int state, int x, int y){
	return viewType::BATTLE;
}

void battleView::updateHealth(float current, float max) {
	if (max == healthDisplay->maxHealth) {
		if (current < healthDisplay->currentHealth) {
			damageTaken = true;
		}
	}

	healthDisplay->currentHealth = current;
	healthDisplay->maxHealth = max;
}

void battleView::setDimensions(int w, int h) {
	int xdiff = w - width;
	int ydiff = h - height;

	takeDamage->rePosition(xdiff, ydiff, w, h);

	gui::setDimensions(w, h);
}