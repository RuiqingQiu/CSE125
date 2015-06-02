#pragma once
#include "numDisplay.h"

class letters;

class healthBar : public guiItem
{
public:
	healthBar();
	healthBar(int x, int y);
	healthBar(int x, int y, bool f);
	healthBar(int x, int y, bool xf, bool yf);
	healthBar(int x, int y, int w, int h);
	healthBar(int x, int y, int w, int h, bool f);
	healthBar(int x, int y, int w, int h, bool xf, bool yf);
	~healthBar();

	float maxHealth;
	float currentHealth;

	virtual void draw();
	virtual void update();
	virtual void rePosition(int x, int y, int w, int h);

	void updateRobotName(string name);

private:
	void init();
	float healthPercent;

	float eWidth = 1000.0 / 1300.0;
	float eHeight = 100.0 / 200.0;
	float wOff = 50.0 / 1300.0;
	float hOff = 50.0 / 200.0;

	vector<letters> roboName;
	numDisplay * maxHealthDisplay;
	numDisplay * currHealthDisplay;

};

