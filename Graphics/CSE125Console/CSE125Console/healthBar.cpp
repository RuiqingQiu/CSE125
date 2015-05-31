#include "stdafx.h"
#include "healthBar.h"
#include "letters.h"


healthBar::healthBar() {
	init();
}

healthBar::healthBar(int x, int y) : numDisplay("HUD/healthBar.png", x, y) {
	init();
}

healthBar::healthBar(int x, int y, bool f) : numDisplay("HUD/healthBar.png", x, y, f) {
	init();
}

healthBar::healthBar(int x, int y, bool xf, bool yf) : numDisplay("HUD/healthBar.png", x, y, xf, yf) {
	init();
}

healthBar::healthBar(int x, int y, int w, int h) : numDisplay("HUD/healthBar.png", x, y, w, h) {
	init();
}

healthBar::healthBar(int x, int y, int w, int h, bool f) : numDisplay("HUD/healthBar.png", x, y, w, h, f) {
	init();
}

healthBar::healthBar(int x, int y, int w, int h, bool xf, bool yf) : numDisplay("HUD/healthBar.png", x, y, w, h, xf, yf) {
	init();
}

healthBar::~healthBar()
{
}

void healthBar::init() {
	setTexture("HUD/healthBar_empty.png", btnState::SELECTED);
	maxHealth = 20;
	currentHealth = maxHealth;

	nSize = height * 35.0/200.0;
	//re-do numbers
	for (int i = 0; i < num_digits; i++) {
		digits[i]->setSize(nSize, nSize);
		digits[i]->setPosition(xPos + width - (width * 40.0 / 1300.0) - (nSize*(i + 3)), yPos + (height / 2.0));
	}

	for (int i = num_digits; i < 4; i++) {
		digits.push_back(new numbers(xPos + width - (width * 20.0 / 1300.0) - (nSize*(i - 1)), yPos + (height / 2.0) - nSize, nSize, nSize, xfixed, yfixed));
	}

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
	nSize = height * 35.0 / 200.0;
	//want to manually make sure it stays relative to time left box
	for (int i = 0; i < num_digits; i++) {
		digits[i]->setPosition(xPos + width - (width * 40.0 / 1300.0) - (nSize*(i + 3)), yPos + (height / 2.0));
	}
	for (int i = num_digits; i < 4; i++) {
		digits[i]->setPosition(xPos + width - (width * 20.0 / 1300.0) - (nSize*(i - 1)), yPos + (height / 2.0) - nSize);
	}

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

	displayValue = currentHealth;
	numDisplay::update();

	int idx = maxHealth;
	for (int i = num_digits; i < 4; i++) {
		if (!(idx >= 0)) break;
		int digit = idx % 10;
		digits[i]->numIdx = digit;
		idx /= 10;
	}
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

	for (int i = 0; i < (int) digits.size(); i++) {
		digits[i]->draw();
	}

	for (int i = 0; i < (int) roboName.size(); i++) {
		roboName[i].draw();
	}

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}