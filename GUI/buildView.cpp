#include "buildView.h"

buildView::buildView() {

    //initialize opengl
    glWidget = new GLWidget;
    QDesktopWidget desktopWidget;
    glWidget->setMinimumWidth(desktopWidget.width()-WINDOWCONST-LISTCONST);

    //initialize widgets
    listOptions = new QListWidget;
    listOptions->setMaximumWidth(LISTCONST);

    //2 ways to add items:
        //this way you don't need row
        new QListWidgetItem(tr("weapons"), listOptions);
        new QListWidgetItem(tr("armor"), listOptions);
        new QListWidgetItem(tr("movement"), listOptions);

        //this way you want it on a certain row
        QListWidgetItem *newItem = new QListWidgetItem;
        newItem->setText(tr("body"));
        listOptions->insertItem(4, newItem);

    battleButton  = new QPushButton(tr("Battle!"));
    helpButton = new QPushButton(tr("Help"));
    helpButton->setMaximumWidth(BUTTONSIZE);

    //create main window layout
    QGridLayout * mainLayout = new QGridLayout;
    mainLayout->addWidget(glWidget, 0, 0);
    mainLayout->addWidget(listOptions, 0, 1);
    mainLayout->addWidget(battleButton, 1,1);
    mainLayout->addWidget(helpButton, 1, 0);

    setLayout(mainLayout);
}

buildView::~buildView()
{

}
