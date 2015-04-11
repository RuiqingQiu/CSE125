
#include "stdafx.h"
#include "gui.h"

class mainMenu : public gui{
public:
	mainMenu();
	mainMenu(int w, int h);
	~mainMenu();

	void VOnRender(); //must have

	void VOnClientUpdate(GameInfoPacket* info); //must have

	//void drawText(int x, int y, std::string text, float r, float g, float b, void * font);

	void setDimensions(int w, int h);
private:
	int width;
	int height;


};