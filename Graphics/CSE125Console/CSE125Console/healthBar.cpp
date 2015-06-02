#include "stdafx.h"
#include "healthBar.h"
#include "letters.h"


healthBar::healthBar() {
	init();
}

healthBar::healthBar(int x, int y) : guiItem("HUD/healthBar.png", x, y) {
	init();
}

healthBar::healthBar(int x, int y, bool f) : guiItem("HUD/healthBar.png", x, y, f) {
	init();
}

healthBar::healthBar(int x, int y, bool xf, bool yf) : guiItem("HUD/healthBar.png", x, y, xf, yf) {
	init();
}

healthBar::healthBar(int x, int y, int w, int h) : guiItem("HUD/healthBar.png", x, y, w, h) {
	init();
}

healthBar::healthBar(int x, int y, int w, int h, bool f) : guiItem("HUD/healthBar.png", x, y, w, h, f) {
	init();
}

healthBar::healthBar(int x, int y, int w, int h, bool xf, bool yf) : guiItem("HUD/healthBar.png", x, y, w, h, xf, yf) {
	init();
}

healthBar::~healthBar()
{
}

void healthBar::init() {
	setTexture("HUD/healthBar_empty.png", btnState::SELECTED);
	maxHealth = 20;
	currentHealth = maxHealth;

	float nSize = height * 60.0/200.0;
	currHealthDisplay = new numDisplay("text/emptyNum.png", xPos + width - (width * 50.0 / 1300.0), yPos + (height / 2.0), nSize, nSize, xfixed, yfixed, 4);
	maxHealthDisplay  = new numDisplay("text/emptyNum.png", xPos + width - (width * 50.0 / 1300.0), yPos + (height / 2.0) - nSize, nSize, nSize, xfixed, yfixed, 4);

	updateRobotName("no name");
}

void healthBar::updateRobotName(string name) {
	if (name == "") return;

	roboName.clear();

	int lSize = height * 36.0 / 200.0;
	int j = 0;
	for (int i = 0; i < (int)name.length(); i++) {
		int test = (int)name.at(i);
		if (test >= 97 && test <= 122) {
			//lower case letters a-z
			test = test - 97;
			roboName.push_back(letters(xPos + (width * 120.0 / 1300) + (lSize * i), yPos + (height * 105.0 / 200.0), lSize, lSize, xfixed, yfixed));
			roboName[j].letterToShow = test;
			roboName[j].offset = i;
			j++;
		}
		else if (test >= 65 && test <= 90) {
			//upper case letters a-z
			test = test - 65;
			roboName.push_back(letters(xPos + (width * 120.0 / 1300) + (lSize * i), yPos + (height * 105.0 / 200.0), lSize, lSize, xfixed, yfixed));
			roboName[j].letterToShow = test;
			roboName[j].offset = i;
			j++;
		}
	}
}

void healthBar:: rePosition(int x, int y, int w, int h) {

	maxHealthDisplay->rePosition(x, y, w, h);
	currHealthDisplay->rePosition(x, y, w, h);

	int lSize = height * 36.0 / 200.0;
	for (int i = 0; i < (int)roboName.size(); i++) {
		roboName[i].setPosition(xPos + (width * 120.0 / 1300) + (lSize * roboName[i].offset), yPos + (height * 105.0 / 200.0));
	}
}

void healthBar::update() {
	//currentHealth -= 0.02;

	if (currentHealth < 0) currentHealth = maxHealth;
	if (currentHealth > maxHealth) currentHealth = maxHealth;
	healthPercent = currentHealth / maxHealth;

	currHealthDisplay->displayValue = currentHealth;
	currHealthDisplay->update();

	maxHealthDisplay->displayValue = maxHealth;
	maxHealthDisplay->update();
}

void healthBar::draw() {
	//bind the texture and draw it
	float wh = width / 2.0;
	float hh = height / 2.0;

	glDisable(GL_LIGHTING);
	glPushMatrix();

	glTranslatef(xPos + wh, yPos + hh, 0.0);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);

	glBindTexture(GL_TEXTURE_2D, texture[currState]);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Make sure no bytes are padded:
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Draw a textured quad
	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-wh, -hh, 0);
	glTexCoord2f(0, 1); glVertex3f(-wh, hh, 0);
	glTexCoord2f(1, 1); glVertex3f(wh, hh, 0);
	glTexCoord2f(1, 0); glVertex3f(wh, -hh, 0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[btnState::SELECTED]);

	glPushMatrix();
	glTranslatef(-width*wOff, -height*hOff, 0.0);

	wh = width * eWidth / 2.0;
	hh = height * eHeight / 2.0;

	// Draw a textured quad
	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
	glTexCoord2f(healthPercent, 0); glVertex3f(-wh + (wh*2.0*healthPercent), -hh, 0);
	glTexCoord2f(healthPercent, 1); glVertex3f(-wh + (wh*2.0*healthPercent), hh, 0);
	glTexCoord2f(1, 1); glVertex3f(wh, hh, 0);
	glTexCoord2f(1, 0); glVertex3f(wh, -hh, 0);
	glEnd();

	glPopMatrix();

	glPopMatrix();

	for (int i = 0; i < (int) roboName.size(); i++) {
		roboName[i].draw();
	}

	currHealthDisplay->draw();
	maxHealthDisplay->draw();

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}