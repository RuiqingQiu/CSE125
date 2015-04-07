#include "battlefieldView.h"

battlefieldView::battlefieldView()
{
    //renderText(20, 100, "Hello Jcy, My first OpenGL app.");

    glWidget = new GLWidget;
    backButton = new QPushButton(tr("Back"));

    QGridLayout * mainLayout = new QGridLayout;
    mainLayout->addWidget(glWidget, 0, 0, 4, 4);
    mainLayout->addWidget(backButton, 0, 0);

    setLayout(mainLayout);
}

battlefieldView::~battlefieldView()
{

}

