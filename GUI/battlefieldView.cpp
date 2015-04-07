#include "battlefieldView.h"

<<<<<<< Updated upstream
battlefieldView::battlefieldView()
{
    //renderText(20, 100, "Hello Jcy, My first OpenGL app.");
=======
battlefieldView::battlefieldView() {
    glWidget = new GLWidget;
    backButton = new QPushButton(tr("Back"));

    QGridLayout * mainLayout = new QGridLayout;
    mainLayout->addWidget(glWidget, 0, 0, 4, 4);
    mainLayout->addWidget(backButton, 0, 0);

    setLayout(mainLayout);
>>>>>>> Stashed changes
}

battlefieldView::~battlefieldView()
{

}

