#ifndef BUILDVIEW_H
#define BUILDVIEW_H

#include <QComboBox>
#include <QListWidget>
#include <QListWidgetItem>

#include "view.h"

static const int LISTCONST = 400;

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

    QListWidget * listOptions;
};

#endif // BUILDVIEW_H
