#include "mainMenu.h"

mainMenu::mainMenu() {
    //load logo image
    QPixmap background;
    background.load("/Users/Tsuruko/CSE125/GUI/testimg.jpg");
    background = background.scaled(this->size(), Qt::IgnoreAspectRatio);

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
    QLabel * img = new QLabel;
    img->setPixmap(background);
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

