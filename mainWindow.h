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
#include <QMenu>
#include <QAction>

class mainWindow : public QMainWindow {
    Q_OBJECT
public:
    mainWindow();
    virtual ~mainWindow();
private:
    Ui::mainWindow widget;
    QSystemTrayIcon *trayIcon;
    QMenu *trayMenu;
    QAction *trayNewDownload;
    QAction *trayQuit;
public slots:
    void on_actionNew_Download_triggered();
    void on_actionAbout_triggered();
    void on_pbAdd_clicked();
};

#endif	/* _MAINWINDOW_H */

