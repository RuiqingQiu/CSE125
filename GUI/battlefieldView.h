#ifndef BATTLEFIELDVIEW_H
#define BATTLEFIELDVIEW_H

#include "view.h"
#include <QtGui>

class battlefieldView : public view
{
public:
    battlefieldView();
    ~battlefieldView();

    QPushButton * backButton;
private:
    GLWidget * glWidget;
};

#endif // BATTLEFIELDVIEW_H
