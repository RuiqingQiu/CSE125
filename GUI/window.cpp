/****************************************************************************
**
** Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "glwidget.h"
#include "window.h"
#include "mainwindow.h"

#include <QSlider>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QPushButton>
#include <QDesktopWidget>
#include <QApplication>
#include <QMessageBox>

Window::Window(MainWindow *mw)
    : mainWindow(mw) {

	// initialize the views
    menu = new mainMenu();
    buildV = new buildView();
    battlefield = new battlefieldView();
    help = new helpMenu();

	// fix the window size to be full screen
    QDesktopWidget desktopWidget;
    setFixedSize(desktopWidget.width()-WINDOWCONST, desktopWidget.height()-WINDOWCONST);
    //showFullScreen();

    // set the main layout when the game starts
	mainLayout = new QVBoxLayout;
    mainLayout->addWidget(menu);
    mainLayout->addWidget(buildV);
    mainLayout->addWidget(battlefield);
    mainLayout->addWidget(help);
    buildV->hide();
    battlefield->hide();
    help->hide();
    currentScreen = menu;
    previousScreen = menu;

    //connect buttons to actions
    connect(menu->playButton, SIGNAL(clicked()), this, SLOT(playButtonPressed()));
    connect(menu->helpButton, SIGNAL(clicked()), this, SLOT(helpButtonPressed()));
    connect(buildV->battleButton, SIGNAL(clicked()), this, SLOT(battleButtonPressed()));
    connect(buildV->helpButton, SIGNAL(clicked()), this, SLOT(helpButtonPressed()));
    connect(help->backButton, SIGNAL(clicked()), this, SLOT(backPressed()));
    connect(battlefield->backButton, SIGNAL(clicked()), this, SLOT(backPressed()));
    connect(battlefield->helpButton, SIGNAL(clicked()), this, SLOT(helpButtonPressed()));

	setLayout(mainLayout);
    setWindowTitle("CSE125 Group 1");
}

void Window::dockUndock() {
    if (parent()) {
        setParent(0);
        setAttribute(Qt::WA_DeleteOnClose);
        move(QApplication::desktop()->width() / 2 - width() / 2,
             QApplication::desktop()->height() / 2 - height() / 2);
        buildV->dockBtn->setText(tr("Dock"));
        show();
    } else {
        if (!mainWindow->centralWidget()) {
            if (mainWindow->isVisible()) {
                setAttribute(Qt::WA_DeleteOnClose, false);
                buildV->dockBtn->setText(tr("Undock"));
                mainWindow->setCentralWidget(this);
            } else {
                QMessageBox::information(0, tr("Cannot dock"), tr("Main window already closed"));
            }
        } else {
            QMessageBox::information(0, tr("Cannot dock"), tr("Main window already occupied"));
        }
    }
}

void Window::playButtonPressed() {
    menu->hide();
    buildV->show();
    battlefield->hide();
    help->hide();
    previousScreen = currentScreen;
    currentScreen = buildV;
}

void Window::battleButtonPressed() {
    menu->hide();
    buildV->hide();
    battlefield->show();
    help->hide();
    previousScreen = currentScreen;
    currentScreen = battlefield;
}

void Window::helpButtonPressed() {
    menu->hide();
    buildV->hide();
    battlefield->hide();
    help->show();
    previousScreen = currentScreen;
    currentScreen = help;
}

void Window::backPressed() {
    currentScreen->hide();
    previousScreen->show();

    view * temp = currentScreen;
    currentScreen = previousScreen;
    previousScreen = temp;
}
