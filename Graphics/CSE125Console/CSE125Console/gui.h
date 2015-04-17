#include "stdafx.h"

#pragma once

#include <string>
#include "GameView.h"

#include <GL/glut.h>
#include "guiItem.h"
#include "button.h"
#include "scrollBox.h"

enum class guiType {
	BUILD,
	BATTLE,
	HELP,
	MENU,
	CONSOLE
};

class gui : public GameView {
public:
	gui();
	gui(int w, int h);
	~gui();

	virtual void VOnRender(); //must have

	virtual void VOnClientUpdate(GameInfoPacket* info); //must have

	void drawText(int x, int y, std::string text, float r, float g, float b, void * font);

	virtual void onClick(int state, int x, int y);

	void setDimensions(int w, int h);

	void set2d();
	void set3d();

	virtual void drawAllItems();

	virtual guiType switchClicked(int state, int x, int y);
	virtual bool helpClicked(int state, int x, int y);
	virtual void passiveMouseFunc(int x, int y);

protected:
	int width;
	int height;

	//regular items, just displays
	std::vector<guiItem*> guiItems;

	//clickable items
	std::vector<button*> buttons;
};

