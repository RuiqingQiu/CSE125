#include "stdafx.h"
#include "helpMenu.h"

helpMenu::helpMenu() : gui() {
	createButtons();
	returnTo = viewType::MENU;
}

helpMenu::helpMenu(int w, int h) : gui(w, h) {
	createButtons();
	returnTo = viewType::MENU;
}

helpMenu::helpMenu(int w, int h, viewType r) : gui(w, h) {
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
    backimg = pages[currentPage];
    
    backButton = new button("menuItem/back.jpg", width*0.45, height * 0.1);
    backButton->setTexture("menuItem/back_sel.jpg", btnState::SELECTED);
    backButton->setTexture("menuItem/back_press.jpg", btnState::PRESSED);
    backButton->setScaling(true, true, width, height);

    next = new button("menuItem/nextPage.jpg", width*0.2, height * 0.1, 116, 30);
    next->setTexture("menuItem/nextPage_sel.jpg", btnState::SELECTED);
    next->setTexture("menuItem/nextPage_press.jpg", btnState::PRESSED);
    next->setScaling(true, true, width, height);

    prev = new button("menuItem/prevPage.jpg", width*0.8, height * 0.1, 116, 30);
    prev->setTexture("menuItem/prevPage_sel.jpg", btnState::SELECTED);
    prev->setTexture("menuItem/prevPage_press.jpg", btnState::PRESSED);
    prev->setScaling(true, true, width, height);

	guiItems.push_back(backimg);
	buttons.push_back(backButton);
}

viewType helpMenu::mouseClickFunc(int state, int x, int y) {
	if (backButton->isSelected(x, height - y) &&
		state == GLUT_UP) {
		return returnTo;
	}
    else if (next->isSelected(x, height - y) &&
             state == GLUT_UP) {
        if (currentPage == MAIN_PAGE) {
            currentPage = BUILD_PAGE;
        } else if (currentPage == BUILD_PAGE) {
            currentPage = BATTLE_PAGE;
        } else {
            currentPage = MAIN_PAGE;
        }
        backimg = pages[currentPage];
    }
    else if (prev->isSelected(x, height - y) &&
             state == GLUT_UP) {
        if (currentPage == BATTLE_PAGE) {
            currentPage = BUILD_PAGE;
        } else if (currentPage == BUILD_PAGE) {
            currentPage = MAIN_PAGE;
        } else {
            currentPage = MAIN_PAGE;
        }
        backimg = pages[currentPage];
    }
	else {
		return viewType::HELP;
	}
}

void helpMenu::VOnRender() {
	gui::VOnRender();
    
    if (currentPage != MAIN_PAGE) {
        prev->draw();
    }
    if (currentPage != BATTLE_PAGE) {
        next->draw();
    }
}