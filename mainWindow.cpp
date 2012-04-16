/*
 * File:   mainWindow.cpp
 * Author: madura
 *
 * Created on April 16, 2012, 8:02 PM
 */

#include "mainWindow.h"
#include <QDesktopWidget>
#include <QIcon>
#include <QInputDialog>

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
    delete trayIcon;
}

void mainWindow::on_actionNew_Download_triggered(){
    bool ok;
    QInputDialog::getText(this, tr("Add new URL"), tr("URL"), QLineEdit::Normal , tr(""), &ok);
}
