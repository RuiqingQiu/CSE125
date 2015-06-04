#include "stdafx.h"
#include "helpMenu.h"

helpMenu::helpMenu() : gui() {
	sound = new Sound();
	createButtons();
	returnTo = viewType::MENU;
}

helpMenu::helpMenu(int w, int h) : gui(w, h) {
	sound = new Sound();
	createButtons();
	returnTo = viewType::MENU;
}

helpMenu::helpMenu(int w, int h, viewType r) : gui(w, h) {
	sound = new Sound();
	createButtons();
	returnTo = r;
}

helpMenu::~helpMenu()
{
}

void helpMenu::createButtons() {
	pages.push_back(new background("help1.jpg", width, height));
    pages.push_back(new background("help2.jpg", width, height));
    pages.push_back(new background("help3.jpg", width, height));
    
    currentPage = MAIN_PAGE;
    
    backButton = new button("menuItem/back.png", width*0.45, 50, 240, 60);
    backButton->setTexture("menuItem/back_sel.png", btnState::SELECTED);
    backButton->setTexture("menuItem/back_press.png", btnState::PRESSED);
    backButton->setScaling(true, true, width, height);

    next = new button("menuItem/nextPage.png", width*0.7, 50, 240, 60);
    next->setTexture("menuItem/nextPage_sel.png", btnState::SELECTED);
    next->setTexture("menuItem/nextPage_press.png", btnState::PRESSED);
    next->setScaling(true, true, width, height);

    prev = new button("menuItem/prevPage.png", width*0.22, 50, 240, 60);
    prev->setTexture("menuItem/prevPage_sel.png", btnState::SELECTED);
    prev->setTexture("menuItem/prevPage_press.png", btnState::PRESSED);
    prev->setScaling(true, true, width, height);

	buttons.push_back(backButton);
	buttons.push_back(next);
	buttons.push_back(prev);
}

viewType helpMenu::mouseClickFunc(int state, int x, int y) {
	if (backButton->isSelected(x, height - y) &&
		state == GLUT_UP) {
		sound->playSelect();
		return returnTo;
	}
    else if (next->isSelected(x, height - y) &&
		state == GLUT_UP && prevMouseState != GLUT_UP) {
        if (currentPage == MAIN_PAGE) {
            currentPage = BUILD_PAGE;
			sound->playSelect();
        } else if (currentPage == BUILD_PAGE) {
			sound->playSelect();
            currentPage = BATTLE_PAGE;
        } else {
            //currentPage = MAIN_PAGE;
        }
    }
    else if (prev->isSelected(x, height - y) &&
		state == GLUT_UP && prevMouseState != GLUT_UP) {
        if (currentPage == BATTLE_PAGE) {
			sound->playSelect();
            currentPage = BUILD_PAGE;
        } else if (currentPage == BUILD_PAGE) {
			sound->playSelect();
            currentPage = MAIN_PAGE;
        } else {
            //currentPage = MAIN_PAGE;
        }
    }
	
	prevMouseState = state;
	return viewType::HELP;
}

void helpMenu::VOnRender() {
	GameView::VOnRender();
	set2d();

	pages[currentPage]->draw();

	if (currentPage != MAIN_PAGE) {
        prev->draw();
    }
    if (currentPage != BATTLE_PAGE) {
        next->draw();
    }

	backButton->draw();

	set3d();
}