#pragma once

#include <string>
#include <GL/glut.h>
#include "GameView.h"
#include "button.h"

class gui : public GameView {
public:
	gui();
	gui(int w, int h);
	~gui();

	void VOnRender(); //must have
	
	void VOnClientUpdate(GameInfoPacket* info); //must have

	void drawText(int x, int y, std::string text, float r, float g, float b, void * font);

	void setDimensions(int w, int h);

	void set2d();
	void set3d();

	void drawButtons();

protected:
	int width;
	int height;

	std::vector<button*> buttons;
};

