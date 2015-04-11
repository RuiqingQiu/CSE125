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
	buttons.push_back(new button("buttonplaceholder.jpg", width-150, 100));
	buttons.push_back(new button("buttonplaceholder.jpg", width - 150, 200));
	buttons.push_back(new button("buttonplaceholder.jpg", width - 150, 300));
	buttons.push_back(new button("buttonplaceholder.jpg", width - 150, 400));

	buttons.push_back(new button("buttonplaceholder.jpg", 50, 50, true));
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