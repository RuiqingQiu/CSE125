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
	guiItem * text = new guiItem("text/time.jpg", width*0.3, height - 38, 200, 38, false, false);
	text->setScaling(true, false, width, height);
	guiItems.push_back(text);

	//text box
	//button jpg dimensions: 1100x990px
	//button texture orignal dimesntions: 1024x1024
	guiItems.push_back(new guiItem("text/textbox.jpg", 20,height-100, 110, 99, true, false));

	//battle button
	//button jpg dimensions: 1000x300px
	//button texture orignal dimesntions: 1024x512
	button * battle = new button("menuItem/battle.jpg", width - 120, 20, 100, 30);
	battle->setTexture("menuItem/battle_sel.jpg", true);
	buttons.push_back(battle);
	
	int scale = 4;
	
	//scroll box
	//scrollbox jpg dimensions: 1000x1600px
	scroll = new scrollBox(width - 250 - 20, 100,
		250, 400);
	buttons.push_back(scroll);

	//list options
	//button jpg width 130px = 256 texture unit
	// border is 10px on img
	for (int i = 0; i < 3; i++) {
		std::string concat = std::to_string(i) + ".jpg";
		scroll->addListItem(concat);
		//sublist, must be added right after the parent list
		for (int j = 0; j < 2; j++) {
			concat = std::to_string((i * 10) + j) + ".jpg";
			scroll->addsubListItem(concat);
		}
	}

	//help button
	//button jpg dimensions: 1000x300px
	//button texture orignal dimesntions: 1024x512
	button * help = new button("menuItem/help.jpg", 20, 20, 100, 30, true);
	help->setTexture("menuItem/help_sel.jpg", true);
	buttons.push_back(help);

}

void buildView::VOnRender() {
	set2d();

	drawAllItems();

	//display text
	//replaced with a texture box now
	//drawText(width*0.4, height - 15, "Time Left:", 1.0, 0.0, 0.0, GLUT_BITMAP_HELVETICA_18);
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

void buildView::onClick(int state, int x, int y) {
	for (int i = 0; i < buttons.size(); i++) {
		//y is goes top to bottom for mouse,
		//and bottom to top for texture >.<
		buttons[i]->onClick(state, x, height-y);
	}
}

guiType buildView::switchClicked(int state, int x, int y) {
	//battle button
	if (buttons[0]->isClicked(x, height - y) &&
		state == GLUT_UP) {
		return guiType::BATTLE;
	}
	else {
		return guiType::BUILD;
	}
}

bool buildView::helpClicked(int state, int x, int y) {
	//help button
	if (state != GLUT_UP) return false;
	return buttons[buttons.size() - 1]->isClicked(x, height - y);
}