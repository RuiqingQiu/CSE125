#include "stdafx.h"
#include "buildView.h"


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

	//battle button
	//button jpg dimensions: 1000x300px
	//button texture orignal dimesntions: 1024x512
	buttons.push_back(new button("buttons/buildView/battle.jpg", width-120, 20, 100, 30, false, true));

	
	int scale = 4;
	
	//scroll box
	//button jpg dimensions: 1320x100px
	//button texture orignal dimesntions: 1024x128
	buttons.push_back(new button("buttons/buildView/up.jpg", width - (1320 / scale) - 20, 90 + (3320 / scale),
															1320/scale, 100/scale, false, true));
	//button jpg dimensions: 1320x3320px
	//button texture orignal dimesntions: 1024x1024
	//didn't think the resolution of opengl would be so awful, need to shrink scrollbox image later to fit 8 items instead of 11
	//also, create scrollbox class?
	//buttons.push_back(new button("buttons/buildView/scrollboxs.jpg", width - 300, 100, false, true));
	buttons.push_back(new button("buttons/buildView/scrollbox.jpg", width - (1320 / scale) - 20, 100,
																	1320/scale, 3320/scale, false, true));
	//button jpg dimensions: 1320x100px
	//button texture orignal dimesntions: 1024x128
	buttons.push_back(new button("buttons/buildView/down.jpg", width - (1320 / scale) - 20, 100 - (100/scale),
															   1320 / scale, 100/scale, false, true));
	
	
	
	//list options
	//button jpg width 130px = 256 texture unit
	// border is 10px on img
	int yPos = 90 + (10/4);
	for (int i = 0; i < 10; i++) {
		//button jpg dimensions: 1300x300px
		//button texture orignal dimesntions: 1024x512
		//border is 10px on img
		buttons.push_back(new button("buttons/buildView/wheels.jpg", width - (1310/scale) - 20, yPos, 1300/scale, 300/scale, false, true));
		yPos += 300 / scale;
	}

	//help button
	//button jpg dimensions: 1000x300px
	//button texture orignal dimesntions: 1024x512
	buttons.push_back(new button("buttons/buildView/help.jpg", 20, 20, 100, 30, true, true));
}

void buildView::VOnRender() {
	set2d();

	//display text
	drawText(width*0.4, height - 15, "Time Left:", 1.0, 0.0, 0.0, GLUT_BITMAP_HELVETICA_18);
	drawText(0, height - 15, "# of deaths:", 1.0, 1.0, 0.0, GLUT_BITMAP_HELVETICA_12);
	drawText(0, height - 25, "# of hits:", 1.0, 1.0, 0.0, GLUT_BITMAP_HELVETICA_12);
	drawText(0, height - 35, "Rank:", 1.0, 1.0, 0.0, GLUT_BITMAP_HELVETICA_12);

	//display number vals for text
	int deaths = 0;
	int hits = 0;
	int rank = 0;
	std::string d = " " + deaths;
	std::string h = " " + hits;
	std::string r = " " + rank;
	drawText(70, height - 15, d, 1.0, 1.0, 0.0, GLUT_BITMAP_HELVETICA_12);
	drawText(70, height - 25, h, 1.0, 1.0, 0.0, GLUT_BITMAP_HELVETICA_12);
	drawText(70, height - 35, r, 1.0, 1.0, 0.0, GLUT_BITMAP_HELVETICA_12);

	drawButtons();

	set3d();
}