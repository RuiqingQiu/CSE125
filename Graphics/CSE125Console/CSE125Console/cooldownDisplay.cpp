#include "stdafx.h"
#include "cooldownDisplay.h"

string cooldownDisplay::textPath = "images/cooldown/cooldown_base.png";

cooldownDisplay::cooldownDisplay() : numDisplay() {
	setMasks();
}

cooldownDisplay::cooldownDisplay(int x, int y) :
numDisplay(textPath, x, y) {
	setMasks();
}

cooldownDisplay::cooldownDisplay(int x, int y, bool f) :
numDisplay(textPath, x, y, f) {
	setMasks();
}

cooldownDisplay::cooldownDisplay(int x, int y, bool xf, bool yf) :
numDisplay(textPath, x, y, xf, yf) {
	setMasks();
}
cooldownDisplay::cooldownDisplay(int x, int y, int w, int h) :
numDisplay(textPath, x, y, w, h) {
	setMasks();
}

cooldownDisplay::cooldownDisplay(int x, int y, int w, int h, bool f) :
numDisplay(textPath, x, y, w, h, f) {
	setMasks();
}

cooldownDisplay::cooldownDisplay(int x, int y, int w, int h, bool xf, bool yf) :
numDisplay(textPath, x, y, w, h, xf, yf) {
	setMasks();
}

cooldownDisplay::~cooldownDisplay()
{
}

bool cooldownDisplay::setMasks() {
	timeLeft = 0;
	maxTime = 5;

	off = (40.0 / 500) * height;
	nSize = (width / 2.0) - off;
	for (int i = 0; i < num_digits; i++) {
		digits[i]->setSize(nSize, nSize);
		digits[i]->setPosition((xPos + width - off) - (nSize*(i + 1)), yPos + (off*4));
	}

	if (cooldown_set) return false;
	for (int i = 0; i < 4; i++) {
		setTexture(i);
	}
	nums_set = true;
	//return true;
}

bool cooldownDisplay::setTexture(int i) {
	//this was setting the individual object's texture, for some reason
	//the multpile instances didn't let display ones

	if (i > 4 || i < 0) return false;
	GLuint * t = &cdMasks[i];
	string concat = path + "images/cooldown/" + std::to_string(i) + ".png";
	*t = SOIL_load_OGL_texture
		(
		concat.c_str()
		,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	if (*t == 0) {
		std::cout << concat.c_str() << std::endl;
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
		return false;
	}

	//return true if successfully set texture
	return true;
}

void cooldownDisplay::update() {
	timeLeft -= 0.05;
	if (timeLeft < 0) timeLeft = maxTime;
	displayValue = timeLeft;
	numDisplay::update();
}

void cooldownDisplay::draw() {
	numDisplay::draw();

	//bind the texture and draw it
	float wh = width / 2.0;
	float hh = height / 2.0;
	float currTime = timeLeft / maxTime;

	glDisable(GL_LIGHTING);
	glPushMatrix();

	glTranslatef(xPos + wh, yPos + hh, 0.0);
	glRotatef(rotation, 0.0, 0.0, 1.0);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Make sure no bytes are padded:
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glBindTexture(GL_TEXTURE_2D, cdMasks[3]);
	
	//top right, then bottom right, then bottom left, then top left
	for (int i = 0; i < 4; i++) {
		glBindTexture(GL_TEXTURE_2D, cdMasks[3]);
		if (currTime > 0.75) {
			if (currTime < (0.75 + 0.1875)) {
				if (currTime < (0.75 + 0.125)) {
					if (currTime < (0.75 + 0.0625)) {
						glBindTexture(GL_TEXTURE_2D, cdMasks[2]);
					}
					else {
						glBindTexture(GL_TEXTURE_2D, cdMasks[1]);
					}
				}
				else {
					glBindTexture(GL_TEXTURE_2D, cdMasks[0]);
				}
			}
			//top right
			glColor3f(1, 1, 1);
			glBegin(GL_QUADS);
			glTexCoord2f(0.5, 0.5); glVertex3f(0, 0, 0);
			glTexCoord2f(0.5, 1); glVertex3f(0, hh, 0);
			glTexCoord2f(1, 1); glVertex3f(wh, hh, 0);
			glTexCoord2f(1, 0.5); glVertex3f(wh, 0, 0);
			glEnd();
		}
		currTime += 0.25;
		glRotatef(-90, 0, 0, 1);
	}

	glPopMatrix();
	//glEnable(GL_LIGHTING);
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);

}

void cooldownDisplay::rePosition(int x, int y, int w, int h) {
	guiItem::rePosition(x, y, w, h);
	off = (40.0 / 500) * height;
	nSize = (width / 2.0) - off;
	//want to manually make sure it stays relative to time left box
	for (int i = 0; i < num_digits; i++) {
		digits[i]->setPosition((xPos + width - off) - (nSize*(i + 1)), yPos + (off * 4));
	}
}