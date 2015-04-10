// main menu ui view extends the gameView
#include "stdafx.h"
#include "GameView.h"
#include <string>
//#include <GL/glut.h>
//#include <vector>
//#include "GeoNode.h"
//#include "GameInfoPacket.h"
//#include "Camera.h"

class mainMenu : public GameView{

public:
	mainMenu();
	~mainMenu();

    void VOnRender(); //must have
	void VOnClientUpdate(GameInfoPacket* info); //must have

	void draw(int width, int height);
	void drawText(int x, int y, std::string text, float r, float g, float b, void * font);

private:
	// window size 
	int width = 512;
    int height = 512;


};