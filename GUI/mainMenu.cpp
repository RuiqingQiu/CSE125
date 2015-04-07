#include "mainMenu.h"

mainMenu::mainMenu()
{
    QDesktopWidget * dw = new QDesktopWidget();
    //load logo image
    //logo = new QImage();

    //initialize buttons
    serverName = new QLineEdit();
    serverName->setPlaceholderText("Enter server address");
    serverName->setStyleSheet("QCustomLineEdit{color: gray;}");
    serverName->setEchoMode(QLineEdit::Normal);
    serverName->setMaximumWidth(300);
    serverName->setMinimumWidth(300);

    robotName = new QLineEdit();
    robotName->setPlaceholderText("Name your robot");
    robotName->setStyleSheet("QCustomLineEdit{color: gray;}");
    robotName->setEchoMode(QLineEdit::Normal);
    robotName->setMaximumWidth(300);
    robotName->setMinimumWidth(300);

    playButton = new QPushButton(tr("Play Now!"));
    playButton->setMaximumWidth(200);
    playButton->setMinimumWidth(200);
    helpButton = new QPushButton(tr("Help"));
    helpButton->setMaximumWidth(200);
    helpButton->setMinimumWidth(200);

    //create a layout for this widget
    QVBoxLayout * mainLayout = new QVBoxLayout();
    mainLayout->setAlignment(Qt::AlignCenter);

    //add content to the layout
    mainLayout->addWidget(serverName);
    mainLayout->addWidget(robotName);
    mainLayout->addWidget(playButton);
    mainLayout->addWidget(helpButton);
    setLayout(mainLayout);

    //align widgets to center
    mainLayout->setAlignment(serverName, Qt::AlignHCenter);
    mainLayout->setAlignment(robotName, Qt::AlignHCenter);
    mainLayout->setAlignment(playButton, Qt::AlignHCenter);
    mainLayout->setAlignment(helpButton, Qt::AlignHCenter);

    //connect buttons to action
}

mainMenu::~mainMenu()
{

}

