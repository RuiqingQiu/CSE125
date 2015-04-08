#include "battlefieldView.h"

battlefieldView::battlefieldView()
{
    //renderText(20, 100, "Hello Jcy, My first OpenGL app.");

    //initialize opengl
    glWidget = new GLWidget;
    QDesktopWidget desktopWidget;
    glWidget->setMinimumWidth(desktopWidget.width()-WINDOWCONST);

    //intialize buttons
    backButton = new QPushButton(tr("Back"));
    backButton->setMaximumWidth(BUTTONSIZE);
    backButton->setMinimumWidth(BUTTONSIZE);
    helpButton = new QPushButton(tr("Help"));
    helpButton->setMaximumWidth(BUTTONSIZE);
    helpButton->setMinimumWidth(BUTTONSIZE);

    //create main layout for window
    QGridLayout * mainLayout = new QGridLayout;
    mainLayout->addWidget(glWidget, 0, 0, 4, 4);
    mainLayout->addWidget(backButton, 0, 0);
    mainLayout->addWidget(helpButton, 3, 3);
    //mainLayout->addWidget(scoreBox, 0, 3);

    setLayout(mainLayout);
}

battlefieldView::~battlefieldView()
{

}

