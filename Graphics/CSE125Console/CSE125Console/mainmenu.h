
#include "stdafx.h"
#include "gui.h"

class mainMenu : public gui{
public:
	mainMenu();
	mainMenu(int w, int h);
	~mainMenu();

	void VOnRender(); //must have

	void VOnClientUpdate(GameInfoPacket* info); //must have

	void onClick(int x, int y);

	//void drawText(int x, int y, std::string text, float r, float g, float b, void * font);

private:
	int width;
	int height;

};