#ifndef BUILDVIEW_H
#define BUILDVIEW_H

#include <QSlider>

#include "views.h"

class buildView : public QWidget
{
public:
    buildView();
    ~buildView();

    QPushButton *dockBtn;
private:
    QSlider *createSlider();

    GLWidget *glWidget;
    QSlider *xSlider;
    QSlider *ySlider;
    QSlider *zSlider;

};

#endif // BUILDVIEW_H
