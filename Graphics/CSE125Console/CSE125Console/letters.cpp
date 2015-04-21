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
		setTexture(i); // a.jpg
	}
	letters_set = true;
	return true;
}

bool letters::setTexture(int i) {

	if (i > 122 || i < 97) return false;
	int index = i - 97;
	GLuint * t = &letter[index];
	char tmp = static_cast<char>(i); // cast to a char
	string pictureName = string(1, tmp); // copy only once
	string concat = path + pictureName + ".jpg";
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