#include "stdafx.h"
#include "guiItem.h"
#include <string>

// optimization, letter only load once
static bool letters_set = false;
static GLuint letter[26];  // hold all the textures

class letters : public guiItem{
	public:
		letters();
		letters(int x, int y);
		letters(int x, int y, bool f);
		letters(int x, int y, bool xf, bool yf);
		letters(int x, int y, int w, int h);
		letters(int x, int y, int w, int h, bool f);
		letters(int x, int y, int w, int h, bool xf, bool yf);
		~letters();

		int letterToShow;
		void init();
		void draw();
		void draw(GLuint * t);
		bool setTexture(int i);
		bool setAllLetters();

};