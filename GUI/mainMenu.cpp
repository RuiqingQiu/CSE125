#include "mainMenu.h"

mainMenu::mainMenu() {
    //setStyleSheet("background-image: url(C:\Users\tsuruko\Documents\GitHub\CSE125\data\testimg.jpg)");
    //load logo image
    //QPixmap logoImg;
    //logoImg.load("/Users/Tsuruko/CSE125/GUI/testimg.jpg");
    //logoImg = logoImg.scaled(this->size(), Qt::IgnoreAspectRatio);

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
    playButton->setMaximumWidth(BUTTONSIZE);
    playButton->setMinimumWidth(BUTTONSIZE);
    helpButton = new QPushButton(tr("Help"));
    helpButton->setMaximumWidth(BUTTONSIZE);
    helpButton->setMinimumWidth(BUTTONSIZE);

    //create a layout for this widget
    QVBoxLayout * mainLayout = new QVBoxLayout();
    mainLayout->setAlignment(Qt::AlignCenter);

    //add content to the layout
    QLabel * img = new QLabel;
    //img->setPixmap(logoImg);
    mainLayout->addWidget(img);
    mainLayout->addWidget(serverName);
    mainLayout->addWidget(robotName);
    mainLayout->addWidget(playButton);
    mainLayout->addWidget(helpButton);

    //align widgets to center
    mainLayout->setAlignment(serverName, Qt::AlignHCenter);
    mainLayout->setAlignment(robotName, Qt::AlignHCenter);
    mainLayout->setAlignment(playButton, Qt::AlignHCenter);
    mainLayout->setAlignment(helpButton, Qt::AlignHCenter);

    setLayout(mainLayout);
}

mainMenu::~mainMenu()
{

}

