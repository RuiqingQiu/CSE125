#ifndef MAINMENU_H
#define MAINMENU_H

#include "view.h"
#include <QLineEdit>
#include <QPushButton>
#include <QImage>

class mainMenu: public view {

public:

    mainMenu();
    ~mainMenu();

//private:

    QImage * logo;

    QLineEdit * serverName;
    QLineEdit * robotName;

    QPushButton * playButton;
    QPushButton * helpButton;
};

#endif // MAINMENU_H
