/*
 * File:   mainWindow.cpp
 * Author: madura
 *
 * Created on April 16, 2012, 8:02 PM
 */

#include "mainWindow.h"
#include <QDesktopWidget>
#include <QIcon>
mainWindow::mainWindow() {
    QIcon tray(":/img/tray.png");
    
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(tray);
    trayIcon->show();
    
    widget.setupUi(this);
    QRect frect = frameGeometry();
    frect.moveCenter(QDesktopWidget().availableGeometry().center());
    move(frect.topLeft());
    
}

mainWindow::~mainWindow() {
}

