#ifndef BUILDVIEW_H
#define BUILDVIEW_H

#include <QComboBox>
#include <QListWidget>

#include "view.h"

static const int NUMOPS = 3;

class buildView : public view
{
public:
    buildView();
    ~buildView();

    QPushButton * dockBtn;
    QPushButton * battleButton;
    QPushButton * helpButton;
private:
    GLWidget * glWidget;

    //temporary, need to learn how to use QListWidget!
    QComboBox * listOptions[NUMOPS];
};

#endif // BUILDVIEW_H
