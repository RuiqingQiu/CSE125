#ifndef MAINMENU_H
#define MAINMENU_H

#include "views.h"
#include <QLineEdit>
#include <QPushButton>
#include <QImage>

class mainMenu: public QWidget
{
public:
    mainMenu();
    ~mainMenu();


private slots:
    void playPressed();
    void helpPressed();
    void enterText();

private:

    QImage * logo;

    QLineEdit * serverName;
    QLineEdit * robotName;

    QPushButton * playButton;
    QPushButton * helpButton;


};

#endif // MAINMENU_H
