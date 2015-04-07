#include "buildView.h"

buildView::buildView() {
    glWidget = new GLWidget;

    //initialize widgets
    for (int i = 0; i < NUMOPS; i++) {
        listOptions[i] = new QComboBox();
        listOptions[i]->addItem(tr("some build option"));
        listOptions[i]->addItem(tr("some build option"));
        listOptions[i]->addItem(tr("some build option"));
    }
    battleButton  = new QPushButton(tr("Battle!"));
    helpButton = new QPushButton(tr("Help"));

    QVBoxLayout * listContainer = new QVBoxLayout;
    for (int i = 0; i < NUMOPS; i++) {
        listContainer->addWidget(listOptions[i]);
    }
    QWidget * myList = new QWidget;
    myList->setLayout(listContainer);

    QGridLayout * mainLayout = new QGridLayout;
    mainLayout->addWidget(glWidget, 0, 0);
    mainLayout->addWidget(myList, 0, 1);
    mainLayout->addWidget(battleButton, 1,1);
    mainLayout->addWidget(helpButton, 1, 0);



    setLayout(mainLayout);
}

buildView::~buildView()
{

}
