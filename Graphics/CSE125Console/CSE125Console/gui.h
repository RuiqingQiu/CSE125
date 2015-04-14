#pragma once

#include <string>
#include <GL/glut.h>
#include "GameView.h"
#include "guiItem.h"
#include "button.h"
#include "scrollBox.h"

//1: build View
//2: battle View
//3: help menu
//4: main menu
//5: switch to console
#define BUILD 1
#define BATTLE 2
#define HELP 3
#define MENU 4
#define CONSOLE 5

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

	virtual int switchClicked(int x, int y);
	virtual bool helpClicked(int x, int y);

protected:
	int width;
	int height;

	//regular items, just displays
	std::vector<guiItem*> guiItems;
	
	//clickable items
	std::vector<button*> buttons;
};

