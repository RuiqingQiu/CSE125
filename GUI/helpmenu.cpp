#include "helpmenu.h"

helpMenu::helpMenu() {

    //initialize buttons and text
    backButton = new QPushButton(tr("Back"));
    backButton->setMaximumWidth(BUTTONSIZE);
    backButton->setMinimumWidth(BUTTONSIZE);

    titleText = new QLabel(tr("Help Menu"));
    //set title font
    QFont font = titleText->font();
    font.setPointSize(24);
    titleText->setFont(font);
    gameDescription = new QLabel(tr("Our game is cool so play it"));
    playInstructions = new QLabel(tr("We have no game instructions for you yet good luck"));

    //create main window layout
    QVBoxLayout * mainLayout = new QVBoxLayout;
    mainLayout->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleText);
    mainLayout->addWidget(gameDescription);
    mainLayout->addWidget(playInstructions);
    mainLayout->addWidget(backButton);

    //align widgets to center
    mainLayout->setAlignment(titleText, Qt::AlignHCenter);
    mainLayout->setAlignment(gameDescription, Qt::AlignHCenter);
    mainLayout->setAlignment(playInstructions, Qt::AlignHCenter);
    mainLayout->setAlignment(backButton, Qt::AlignHCenter);

    setLayout(mainLayout);
}

helpMenu::~helpMenu() {

}

