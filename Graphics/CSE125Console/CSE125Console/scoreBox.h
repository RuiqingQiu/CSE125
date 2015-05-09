#pragma once
#include "guiItem.h"
#include "numbers.h"

#define MAX_DIGITS 2

class scoreBox : public guiItem {
public:
	scoreBox();
	scoreBox(int x, int y);
	scoreBox(int x, int y, bool f);
	scoreBox(int x, int y, bool xf, bool yf);
	scoreBox(int x, int y, int w, int h);
	scoreBox(int x, int y, int w, int h, bool f);
	scoreBox(int x, int y, int w, int h, bool xf, bool yf);
	~scoreBox();

	void update();
	void draw();
	void rePosition(int x, int y, int w, int h);

	void updateScore(int d, int h, int r);

	static string textPath;

	//hardcoded values based on texture size
	static double border;
	static double spacing;
	static double sizing;

private:
	int deaths;
	int hits;
	int rank;

	void createNumbers();

	numbers * deathDigits[MAX_DIGITS];
	numbers * hitDigits[MAX_DIGITS];
	numbers * rankDigits[MAX_DIGITS];
};

