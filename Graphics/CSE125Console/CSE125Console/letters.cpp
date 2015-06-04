#include "stdafx.h"
#include "letters.h"

using namespace std;

letters::letters() {
	init();
	setAllLetters();
}

letters::letters(int x, int y) {
	init();
	setPosition(x, y);
	setAllLetters();
}

letters::letters(int x, int y, bool f) {
	init();
	setPosition(x, y);
	setFixed(f, f);
	setAllLetters();
}

letters::letters(int x, int y, bool xf, bool yf) {
	init();
	setPosition(x, y);
	setFixed(xf, yf);
	setAllLetters();
}

letters::letters(int x, int y, int w, int h) {
	init();
	setPosition(x, y);
	setSize(w, h);
	setAllLetters();
}

letters::letters(int x, int y, int w, int h, bool f) {
	init();
	setPosition(x, y);
	setSize(w, h);
	setFixed(f, f);
	setAllLetters();
}

letters::letters(int x, int y, int w, int h, bool xf, bool yf) {
	init();
	setPosition(x, y);
	setSize(w, h);
	setFixed(xf, yf);
	setAllLetters();
}

letters::~letters() {

}

void letters::init() {
	setPosition(0, 0);
	setSize(100, 100);
	setFixed(false, true);
	sWidth = 0;
	sHeight = 0;
	currState = btnState::NORMAL;
	scaleX = false;
	scaleY = false;
	path = "uiItem/text/letters/";
}


bool letters::setAllLetters() {
	if (letters_set) return false;
	// ascii a-z goes from 97 to 122
	for (int i = 97; i < 123; i++) {
		setTexture(i); // a.png
	}
	letters_set = true;
	return true;
}

// set the texture
bool letters::setTexture(int i) {
	if (i > 122 || i < 97) return false;
	int index = i - 97;
	GLuint * t = &letter[index];
	char tmp = static_cast<char>(i); // cast to a char
	string pictureName = string(1, tmp); // copy only once
	string concat = path + pictureName + ".png";
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


//this was drawing the number object's individual texture
//bind the texture and draw it
void letters::draw() {
	glDisable(GL_LIGHTING);
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);

	glBindTexture(GL_TEXTURE_2D, letter[letterToShow]);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Make sure no bytes are padded:
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Draw a textured quad
	//glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(xPos, yPos, 0);
	glTexCoord2f(0, 1); glVertex3f(xPos, yPos + height, 0);
	glTexCoord2f(1, 1); glVertex3f(xPos + width, yPos + height, 0);
	glTexCoord2f(1, 0); glVertex3f(xPos + width, yPos, 0);
	glEnd();

	glPopMatrix();
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}

//this is attempt to make them draw referencing the same stored texture,
//but it didn't change anything
void letters::draw(GLuint * t) {
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