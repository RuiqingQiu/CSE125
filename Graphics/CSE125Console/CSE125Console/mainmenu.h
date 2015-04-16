
#include "stdafx.h"
#include "gui.h"

class mainMenu : public gui {
public:
	mainMenu();
	mainMenu(int w, int h);
	~mainMenu();

	void VOnRender(); //must have

	void VOnClientUpdate(GameInfoPacket* info); //must have

	void onClick(int state, int x, int y);

	void createButtons();

	guiType switchClicked(int state, int x, int y);
	bool helpClicked(int state, int x, int y);

	vector<button*> clickableItems;

};