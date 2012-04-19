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
#include <QStandardItemModel>
#include <QStringList>

mainWindow::mainWindow() {
    widget.setupUi(this);
    QIcon tray(":/img/tray.png");
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(tray);
    
    trayMenu = new QMenu();
    trayNewDownload = new QAction(tr("&New"), this);
    trayMenu->addAction(trayNewDownload);
    QObject::connect(trayNewDownload, SIGNAL(triggered()), this, SLOT(on_actionNew_Download_triggered()));
    
    trayQuit = new QAction(tr("&Quit"), this);
    trayMenu->addAction(trayQuit);
    QObject::connect(trayQuit, SIGNAL(triggered()), this, SLOT(close()));
    
    trayIcon->setContextMenu(trayMenu);
    trayIcon->show();
    QStandardItemModel *m=new QStandardItemModel();
    
    m->setColumnCount(2);
    QStandardItem *s = new QStandardItem(tr("sad&a"));
    s->setEditable(false);
    m->insertRow(0,s);
    m->setHorizontalHeaderItem(0, new QStandardItem(tr("sad&a")));
    QStringList *sl= new QStringList();
    *sl<<"as"<<"asas";
    m->setHorizontalHeaderLabels(*sl);
    widget.lstDownloads->setItemsExpandable(false);
    widget.lstDownloads->setModel(m);

    QRect frect = frameGeometry();
    frect.moveCenter(QDesktopWidget().availableGeometry().center());
    move(frect.topLeft());
}

mainWindow::~mainWindow() {
    delete trayIcon;
    delete trayMenu;
    delete trayNewDownload;
    delete trayQuit;
}

void mainWindow::on_actionNew_Download_triggered(){
    bool ok;
    QInputDialog::getText(this, tr("Add new URL"), tr("URL"), QLineEdit::Normal , tr(""), &ok);
}
void mainWindow::on_pbAdd_clicked(){
    on_actionNew_Download_triggered();
}
void mainWindow::on_actionAbout_triggered(){
    
}