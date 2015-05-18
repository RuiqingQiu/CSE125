#pragma once
#include "numDisplay.h"

//global static variables to load numbers only once
static bool cooldown_set = false;
static GLuint cdMasks[4];

class cooldownDisplay : public numDisplay
{
public:
	cooldownDisplay();
	cooldownDisplay(int x, int y);
	cooldownDisplay(int x, int y, bool f);
	cooldownDisplay(int x, int y, bool xf, bool yf);
	cooldownDisplay(int x, int y, int w, int h);
	cooldownDisplay(int x, int y, int w, int h, bool f);
	cooldownDisplay(int x, int y, int w, int h, bool xf, bool yf);
	~cooldownDisplay();


	bool setMasks();

	bool setTexture(int i);
	virtual void update();
	virtual void draw();
	virtual void rePosition(int x, int y, int w, int h);

	static string textPath;

	float timeLeft;
	float maxTime;
};

