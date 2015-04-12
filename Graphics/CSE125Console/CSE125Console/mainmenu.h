
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

	vector<button*> clickableItems;


private:
	int width;
	int height;

};