#include "helpmenu.h"

helpMenu::helpMenu() {

    backButton = new QPushButton(tr("Back"));

    QGridLayout * mainLayout = new QGridLayout;

    mainLayout->addWidget(backButton);

    setLayout(mainLayout);
}

helpMenu::~helpMenu() {

}

