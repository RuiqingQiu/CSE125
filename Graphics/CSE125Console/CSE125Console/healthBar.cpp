#include "stdafx.h"
#include "healthBar.h"


healthBar::healthBar() {
	init();
}

healthBar::healthBar(int x, int y) : guiItem("images/healthBar.jpg", x, y) {
	init();
}

healthBar::healthBar(int x, int y, bool f) : guiItem("images/healthBar.jpg", x, y, f) {
	init();
}

healthBar::healthBar(int x, int y, bool xf, bool yf) : guiItem("images/healthBar.jpg", x, y, xf, yf) {
	init();
}

healthBar::healthBar(int x, int y, int w, int h) : guiItem("images/healthBar.jpg", x, y, w, h) {
	init();
}

healthBar::healthBar(int x, int y, int w, int h, bool f) : guiItem("images/healthBar.jpg", x, y, w, h, f) {
	init();
}

healthBar::healthBar(int x, int y, int w, int h, bool xf, bool yf) : guiItem("images/healthBar.jpg", x, y, w, h, xf, yf) {
	init();
}

healthBar::~healthBar()
{
}

void healthBar::init() {
	setTexture("images/healthBar_empty.jpg", btnState::SELECTED);
	maxHealth = 1000;
	currentHealth = maxHealth;
}

void healthBar::update() {

	//currentHealth -= 1;

	if (currentHealth < 0) currentHealth = maxHealth;

	if (currentHealth > maxHealth) currentHealth = maxHealth;

	healthPercent = currentHealth / maxHealth;
}

void healthBar::draw() {
	//bind the texture and draw it

	glDisable(GL_LIGHTING);
	glPushMatrix();
	//glLoadMatrixd(glmatrix.getPointer());

	glEnable(GL_TEXTURE_2D);
	//glActiveTexture(GL_TEXTURE1);

	glBindTexture(GL_TEXTURE_2D, texture[btnState::NORMAL]);

	// Make sure no bytes are padded:
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Draw a textured quad
	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(xPos, yPos, 0);
	glTexCoord2f(0, 1); glVertex3f(xPos, yPos + height, 0);
	glTexCoord2f(1, 1); glVertex3f(xPos + width, yPos + height, 0);
	glTexCoord2f(1, 0); glVertex3f(xPos + width, yPos, 0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[btnState::SELECTED]);
	// Draw a textured quad
	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
	glTexCoord2f(healthPercent, 0); glVertex3f(xPos + (width*healthPercent), yPos, 0);
	glTexCoord2f(healthPercent, 1); glVertex3f(xPos + (width*healthPercent), yPos + height, 0);
	glTexCoord2f(1, 1); glVertex3f(xPos + width, yPos + height, 0);
	glTexCoord2f(1, 0); glVertex3f(xPos + width, yPos, 0);
	glEnd();

	glPopMatrix();
	//glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
}