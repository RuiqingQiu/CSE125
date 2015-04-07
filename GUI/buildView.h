#ifndef BUILDVIEW_H
#define BUILDVIEW_H

#include <QComboBox>

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

    //array of combo box for now... need to make a selector
    QComboBox * listOptions[NUMOPS];
};

#endif // BUILDVIEW_H
