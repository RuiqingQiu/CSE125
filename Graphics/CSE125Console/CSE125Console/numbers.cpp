#include "stdafx.h"
#include "numbers.h"


numbers::numbers() {
	init();
	setAllNumbers();
}

numbers::numbers(int x, int y) {
	init();
	setPosition(x, y);
	setAllNumbers();
}

numbers::numbers(int x, int y, bool f) {
	init();
	setPosition(x, y);
	setFixed(f, f);
	setAllNumbers();
}

numbers::numbers(int x, int y, bool xf, bool yf) {
	init();
	setPosition(x, y);
	setFixed(xf, yf);
	setAllNumbers();
}

numbers::numbers(int x, int y, int w, int h) {
	init();
	setPosition(x, y);
	setSize(w, h);
	setAllNumbers();
}

numbers::numbers(int x, int y, int w, int h, bool f) {
	init();
	setPosition(x, y);
	setSize(w, h);
	setFixed(f, f);
	setAllNumbers();
}

numbers::numbers(int x, int y, int w, int h, bool xf, bool yf) {
	init();
	setPosition(x, y);
	setSize(w, h);
	setFixed(xf, yf);
	setAllNumbers();
}

numbers::~numbers() {

}

void numbers::init() {
	numIdx = 0;
	setPosition(0, 0);
	setSize(100, 100);
	setFixed(false, true);
	sWidth = 0;
	sHeight = 0;
	currState = btnState::NORMAL;
	scaleX = false;
	scaleY = false;
	path = "uiItem/text/numbers/";
}

bool numbers::setAllNumbers() {
	if (nums_set) return false;
	for (int i = 0; i < 10; i++) {
		setTexture(i);
	}
	nums_set = true;
	return true;
}

bool numbers::setTexture(int i) {
	//this was setting the individual object's texture, for some reason
	//the multpile instances didn't let display ones

	if (i > 9 || i < 0) return false;
	GLuint * t = &nums[i];
	string concat = path + std::to_string(i) + ".png";
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

void numbers::draw() {
	//this was drawing the number object's individual texture

	//bind the texture and draw it

	glDisable(GL_LIGHTING);
	glPushMatrix();
	//glLoadMatrixd(glmatrix.getPointer());

	glEnable(GL_TEXTURE_2D);
	//glActiveTexture(GL_TEXTURE1);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, nums[numIdx]);
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

	glPopMatrix();
	//glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

}

void numbers::draw(GLuint * t) {
	//this is attempt to make them draw referencing the same stored texture,
	//but it didn't change anything

	//bind the texture and draw it

	glDisable(GL_LIGHTING);
	glPushMatrix();
	//glLoadMatrixd(glmatrix.getPointer());

	glEnable(GL_TEXTURE_2D);
	//glActiveTexture(GL_TEXTURE1);

	glBindTexture(GL_TEXTURE_2D, *t);
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

	glPopMatrix();
	//glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

}