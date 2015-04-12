#pragma once

#include <string>
#include <GL/glut.h>
#include "GameView.h"
#include "guiItem.h"
#include "button.h"
#include "scrollBox.h"

class gui : public GameView {
public:
	gui();
	gui(int w, int h);
	~gui();

	void VOnRender(); //must have
	
	void VOnClientUpdate(GameInfoPacket* info); //must have

	void drawText(int x, int y, std::string text, float r, float g, float b, void * font);

	virtual void onClick(int x, int y);

	void setDimensions(int w, int h);

	void set2d();
	void set3d();

	void drawAllItems();

protected:
	int width;
	int height;

	//regular items, just displays
	std::vector<guiItem*> guiItems;
	
	//clickable items
	std::vector<button*> buttons;
};

