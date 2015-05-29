#pragma once

#include <map>

#include "guiItem.h"
#include "Definition.h"
class blockDescriptions : public guiItem {
public:
	blockDescriptions();
	blockDescriptions(int x, int y);
	blockDescriptions(int x, int y, bool f);
	blockDescriptions(int x, int y, bool xf, bool yf);
	blockDescriptions(int x, int y, int w, int h);
	blockDescriptions(int x, int y, int w, int h, bool f);
	blockDescriptions(int x, int y, int w, int h, bool xf, bool yf);
	~blockDescriptions();

	//update
	virtual void update();

	//drawing functions
	virtual void draw();
	virtual void rePosition(int x, int y, int w, int h);

	int currDescription;
private:
	static string textPath;

	std::map<int, guiItem *> descriptions;

	void addDescriptions(int x, int y, int w, int h, bool xf, bool yf);

};

