#ifndef HELPMENU_H
#define HELPMENU_H

#include <QTextLayout>
#include <QPainter>

#include "view.h"

class helpMenu : public view {

public:
    helpMenu();
    ~helpMenu();


    QPushButton * backButton;

private:
    QLabel * titleText;
    QLabel * gameDescription;
    QLabel * playInstructions;
};

#endif // HELPMENU_H
