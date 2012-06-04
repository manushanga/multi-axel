/* 
 * File:   mainWindow.h
 * Author: madura
 *
 * Created on April 16, 2012, 8:02 PM
 */

#ifndef _MAINWINDOW_H
#define	_MAINWINDOW_H

#include "ui_mainWindow.h"

#include <semaphore.h>

#include "QSystemTrayIcon"
#include <QMenu>
#include <QAction>
#include <axel.h>
#include <QStandardItemModel>

class mainWindow : public QMainWindow {
    Q_OBJECT
public:
    mainWindow(bool *up);
    void startNewDownload(QString url, bool paused);
    virtual ~mainWindow();
private:
    Ui::mainWindow widget;
    QSystemTrayIcon *trayIcon;
    QMenu *trayMenu;
    QAction *trayNewDownload;
    QAction *trayQuit;
    QStandardItemModel *listModel;
    vector<Axel *> *axels;
    AxelSettings *settings;
    pthread_t th_updater;
    void setSettings();
    void getSettings();
    static void *thread_updater(void *obj);
    sem_t update_lock;
public slots:
    void on_actionNew_Download_triggered();
    void on_actionAbout_triggered();
    void on_actionSettings_triggered();
    void on_pbAdd_clicked();
    void on_pbStart_clicked();
    void on_pbStop_clicked();
    void on_pbRemove_clicked();
    void on_lstDownloads_doubleClicked(QModelIndex qi);
};

#endif	/* _MAINWINDOW_H */

