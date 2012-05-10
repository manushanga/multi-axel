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
#include <QStringList>
enum cols{DL_NAME=0, DL_STATUS, DL_PERCENTAGE, DL_SPEED};
QString colnames[4] = {"Name", "Status","Percentage","Speed"};
QString statenames[6] = {"Downloading", "Paused", "Done", "Error", 
    "Unknown", "No multi-connections"};

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
    listModel = new QStandardItemModel();
    
    listModel->setColumnCount(4);
    QStringList *sl= new QStringList();
    *sl<<colnames[0]<<colnames[1]<<colnames[2]<<colnames[3];
    listModel->setHorizontalHeaderLabels(*sl);
    widget.lstDownloads->setItemsExpandable(false);
    widget.lstDownloads->setModel(listModel);

    axels = new vector<Axel *>;
    QRect frect = frameGeometry();
    frect.moveCenter(QDesktopWidget().availableGeometry().center());
    move(frect.topLeft());
    
    pthread_create(&this->th_updater, NULL, &mainWindow::thread_updater, this);
}

mainWindow::~mainWindow() {
    pthread_cancel(this->th_updater);
    delete trayIcon;
    delete trayMenu;
    delete trayNewDownload;
    delete trayQuit;
}
void *mainWindow::thread_updater(void * obj){
    mainWindow *w = (mainWindow *) obj;
    while (1) {
        if (w->axels->size()>0 ){
            for (int row=0;row<w->axels->size();row++) {
                Axel *a = w->axels->at(row);
                state_t status = a->getStatus();
               // DPRINT("%d",status);
                w->listModel-> item(row, DL_STATUS)->setText(statenames[status]);
                if (status == AXEL_DOWNLOADING || status == AXEL_NOMULTI) {
                    QString qa;
                    qa.sprintf("%f",a->getSpeed());
                    w->listModel-> item(row, DL_SPEED)->setText(qa);

                    qa.sprintf("%d",a->getPercentage());
                    w->listModel-> item(row, DL_PERCENTAGE)->setText(qa);
                } else if (status == AXEL_UNKNOWN || status == AXEL_ERROR) {
                    QString qa;
                    qa.sprintf("%f", 0.0f );
                    w->listModel-> item(row, DL_SPEED)->setText(qa);
                    
                    qa.sprintf("%d", 0);
                    w->listModel-> item(row, DL_PERCENTAGE)->setText(qa);

                    
                }
            }
            sleep(1);
        }
    }
    return NULL;
}
void mainWindow::startNewDownload(QString url){
    AxelSettings s;
    s.httpProxy = "";
    s.maxSpeed = 0;
    s.numberOfConnections = 10;
    s.userAgent = "";
    s.outputPath = "/home/madura/Downloads/ss.zip";
    char *f="http://www.openworlds.org/data/The.Cove.2009.LIMITED.DVDRip.XviD-AMIABLE/The.Cove.2009.LIMITED.DVDRip.XviD-AMIABLE.avi";
    char *jk="http://joomlacode.org/gf/download/frsrelease/16914/73508/Joomla_2.5.4-Stable-Full_Package.zip";
    Axel *a = new Axel(url.toStdString(), s);
    a->start();
    this->listModel->setItem(axels->size(), DL_NAME, new QStandardItem());
    this->listModel->setItem(axels->size(), DL_STATUS, new QStandardItem());
    this->listModel->setItem(axels->size(), DL_PERCENTAGE, new QStandardItem());
    this->listModel->setItem(axels->size(), DL_SPEED, new QStandardItem());
    
    this->listModel->item(axels->size(), DL_NAME)->setText(QString::fromStdString(a->getName()));
    axels->push_back(a);
}
void mainWindow::on_actionNew_Download_triggered(){
    bool ok;
    this->startNewDownload(QInputDialog::getText(this, tr("Add new URL"), tr("URL"), QLineEdit::Normal , tr(""), &ok));
}
void mainWindow::on_pbAdd_clicked(){
    on_actionNew_Download_triggered();
}
void mainWindow::on_actionAbout_triggered(){
    
}