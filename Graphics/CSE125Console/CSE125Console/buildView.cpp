#include "stdafx.h"
#include "buildView.h"

/*
 * things to implement:
 * on click actions
 */

buildView::buildView() {
	width = 0;
	height = 0;
	createButtons();
}

buildView::buildView(int w, int h) {
	width = w;
	height = h;
	createButtons();
}

buildView::~buildView()
{
}

void buildView::createButtons() {
	//hardcoded button sizes for now

	//text displays
	//text are png for transparent background
	//however, transparency isn't working? might be soil converter... will have to try something else
	//button jpg dimensions: 1000x192px
	//button texture orignal dimesntions: 1024x256
	//guiItems.push_back(new guiItem("uiItem/text/time.png", 20, height - 100, 110, 99, true, false));

	//text box
	//button jpg dimensions: 1100x990px
	//button texture orignal dimesntions: 1024x1024
	guiItems.push_back(new guiItem("uiItem/text/textbox.jpg", 20,height-100, 110, 99, true, false));

	//battle button
	//button jpg dimensions: 1000x300px
	//button texture orignal dimesntions: 1024x512
	buttons.push_back(new button("uiItem/buttons/menuItem/battle.jpg", width-120, 20, 100, 30));
	
	int scale = 4;
	
	//scroll box
	//button jpg dimensions: 1320x2420px
	//button texture orignal dimesntions: 1024x1024
	scroll = new scrollBox(width - (1320 / scale) - 20, 100,
		1320 / scale, 2420 / scale);
	guiItems.push_back(scroll);
	
	//list options
	//button jpg width 130px = 256 texture unit
	// border is 10px on img
	for (int i = 0; i < 8; i++) {
		scroll->addListItem("uiItem/buttons/listItem/wheels.jpg");
	}

	//help button
	//button jpg dimensions: 1000x300px
	//button texture orignal dimesntions: 1024x512
	buttons.push_back(new button("uiItem/buttons/menuItem/help.jpg", 20, 20, 100, 30, true));
}

void buildView::VOnRender() {
	set2d();

	drawAllItems();

	//display text
	drawText(width*0.4, height - 15, "Time Left:", 1.0, 0.0, 0.0, GLUT_BITMAP_HELVETICA_18);
	//replaced with a text box texture now!
	//drawText(0, height - 15, "# of deaths:", 1.0, 1.0, 0.0, GLUT_BITMAP_HELVETICA_12);
	//drawText(0, height - 25, "# of hits:", 1.0, 1.0, 0.0, GLUT_BITMAP_HELVETICA_12);
	//drawText(0, height - 35, "Rank:", 1.0, 1.0, 0.0, GLUT_BITMAP_HELVETICA_12);

	//display number vals for text... please replace with game logic numbers
	int deaths = 0;
	int hits = 0;
	int rank = 0;

	std::string d = " " + std::to_string(deaths);
	std::string h = " " + std::to_string(hits);
	std::string r = " " + std::to_string(rank);
	//using drawtext for now... ugly font though
	drawText(70, height - 15, d, 1.0, 1.0, 0.0, GLUT_BITMAP_HELVETICA_12);
	drawText(70, height - 25, h, 1.0, 1.0, 0.0, GLUT_BITMAP_HELVETICA_12);
	drawText(70, height - 35, r, 1.0, 1.0, 0.0, GLUT_BITMAP_HELVETICA_12);

	set3d();
}