#pragma once

#include <string>
#include <GL/glut.h>

#include "GameView.h"

class gui : public GameView {
public:
	gui();
	gui(int w, int h);
	~gui();

	void VOnRender(); //must have
	
	void VOnClientUpdate(GameInfoPacket* info); //must have

	void drawText(int x, int y, std::string text, float r, float g, float b, void * font);

	void setDimensions(int w, int h);
private:
	int width;
	int height;
};

