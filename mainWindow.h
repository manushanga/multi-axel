/* 
 * File:   mainWindow.h
 * Author: madura
 *
 * Created on April 16, 2012, 8:02 PM
 */

#ifndef _MAINWINDOW_H
#define	_MAINWINDOW_H

#include "ui_mainWindow.h"
#include "QSystemTrayIcon"

class mainWindow : public QMainWindow {
    Q_OBJECT
public:
    mainWindow();
    virtual ~mainWindow();
private:
    Ui::mainWindow widget;
    QSystemTrayIcon *trayIcon;
};

#endif	/* _MAINWINDOW_H */

