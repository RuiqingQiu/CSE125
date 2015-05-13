
#pragma once
#include "stdafx.h"
#include <string>
#include "GameView.h"

#include <GL/glut.h>
#include "guiItem.h"
#include "button.h"
#include "background.h"
#include "scrollBox.h"
#include "scoreBox.h"

class gui : public GameView {
public:
	gui();
	gui(int w, int h);
	~gui();

	virtual void VOnRender(); //must have
	virtual void VOnClientUpdate(GameInfoPacket* info); //must have
	virtual void VUpdate();

	void setDimensions(int w, int h);

	//draw 2d ui functions
	void set2d();
	void set3d();
	virtual void drawAllItems();
	void drawText(int x, int y, std::string text, float r, float g, float b, void * font);

	//mouse click functions
	virtual viewType mouseClickFunc(int state, int x, int y);
	virtual void passiveMouseFunc(int x, int y);

	void addItem(guiItem * item);

	

protected:
	int width;
	int height;

	//regular items, just displays
	std::vector<guiItem*> guiItems;

	//clickable items
	std::vector<button*> buttons;
};

