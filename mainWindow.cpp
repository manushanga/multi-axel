/*
 * File:   mainWindow.cpp
 * Author: madura
 *
 * Created on April 16, 2012, 8:02 PM
 */
#include <unistd.h>

#include "mainWindow.h"
#include <QDesktopWidget>
#include <QIcon>
#include <QInputDialog>
#include <QStringList>
#include <QItemSelectionModel>
#include <QSettings>
#include <fstream>
#include <string>

#include "settingsWindow.h"
#include "aboutWindow.h"


enum cols{DL_NAME=0, DL_STATUS, DL_PERCENTAGE, DL_SPEED};

QString colnames[4] = {"Name", "Status","Percentage","Speed"};
QString statenames[6] = {"Downloading", "Paused", "Done", "Error", 
    "Unknown", "No multi-connections"};
void mainWindow::getSettings(){
    bool ok;
    QSettings qs("MaduraA","MultiAxel");
    qs.beginGroup("Settings");
    this->settings->httpProxy = qs.value("httpProxy").toString().toStdString();
    this->settings->ftpProxy = qs.value("ftpProxy").toString().toStdString();
    this->settings->maxSpeed = qs.value("maxSpeed").toInt(&ok);
    this->settings->numberOfConnections = qs.value("numberOfConnections").toInt(&ok);
    this->settings->userAgent = qs.value("userAgent").toString().toStdString();
    this->settings->outputPath = qs.value("outputPath").toString().toStdString();
    this->settings->workingDirectory = qs.value("workingDirectory").toString().toStdString();        
    qs.endGroup();
}
void mainWindow::setSettings(){
    QSettings qs("MaduraA","MultiAxel");
    qs.beginGroup("Settings");
    qs.setValue("httpProxy", QVariant(QString().fromStdString(this->settings->httpProxy)));
    qs.setValue("ftpProxy",QVariant(QString().fromStdString(this->settings->ftpProxy)));
    qs.setValue("maxSpeed",QVariant(this->settings->maxSpeed));
    qs.setValue("numberOfConnections", QVariant(this->settings->numberOfConnections));
    qs.setValue("userAgent",QVariant(QString().fromStdString(this->settings->userAgent)));
    qs.setValue("outputPath",QVariant(QString().fromStdString(this->settings->outputPath)));
    qs.setValue("workingDirectory", QVariant(QString().fromStdString(this->settings->workingDirectory)));
    qs.endGroup();
    qs.sync();
}
mainWindow::mainWindow(bool *up) {
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
    this->settings = new AxelSettings;
    QSettings qs("MaduraA","MultiAxel");
    
    if (qs.allKeys().size()!=0) {
        getSettings();
        int lst = qs.beginReadArray("List");
        if (lst>0) {
            bool ok;
            for (int i=0;i<lst;i++) {
                qs.setArrayIndex(i);
                this->startNewDownload(qs.value("url").toString(), true);
                int status = qs.value("status").toInt(&ok);
                this->listModel->item(i, DL_STATUS )->setText( statenames[status]);
            }
        }
        qs.endArray();
    } else {
        this->settings->httpProxy = "";
        this->settings->ftpProxy = "";
        this->settings->maxSpeed = 0;
        this->settings->numberOfConnections = 10;
        this->settings->userAgent = "";
        this->settings->outputPath = "";
        this->settings->workingDirectory = string("/home/") + string(getenv("USER")) +string("/Downloads");
        
        setSettings();
    }

    QRect frect = frameGeometry();
    frect.moveCenter(QDesktopWidget().availableGeometry().center());
    move(frect.topLeft());

    pthread_create(&this->th_updater, NULL, &mainWindow::thread_updater, this);
    *up = true;
}
mainWindow::~mainWindow() {
    pthread_cancel(this->th_updater);
    QSettings qs("MaduraA","MultiAxel");
    for (int i=0;i<this->axels->size();i++) {
        qs.setArrayIndex(i);
        qs.setValue("url", QVariant(QString().fromStdString(this->axels->at(i)->getUrl())));
        qs.setValue("status", QVariant((int) this->axels->at(i)->getStatus()));
    }
    delete trayIcon;
    delete trayMenu;
    delete trayNewDownload;
    delete trayQuit;
    delete listModel;
    delete settings;
}
void *mainWindow::thread_updater(void * obj){
    mainWindow *w = (mainWindow *) obj;
    while (1) {
        if (w->axels->size()>0 ){
            for (size_t row=0;row<w->axels->size();row++) {
                Axel *a = w->axels->at(row);
                state_t status = a->getStatus();
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
                } else if (status == AXEL_DONE) {
                    QString qa;
                    qa.sprintf("%f", 0.0f );
                    w->listModel-> item(row, DL_SPEED)->setText(qa);
                    
                    qa.sprintf("%d", 100);
                    w->listModel-> item(row, DL_PERCENTAGE)->setText(qa);      
                }
            }          
        }
        usleep(900);
    }
    return NULL;
}
void mainWindow::startNewDownload(QString url, bool paused){
    url = url.trimmed();
    if (url.size() == 0 )
        return;
    Axel *a = new Axel(url.toStdString(), *this->settings);
    if (paused == false)
        a->start();
    this->listModel->setItem(axels->size(), DL_NAME, new QStandardItem());
    this->listModel->setItem(axels->size(), DL_STATUS, new QStandardItem());
    this->listModel->setItem(axels->size(), DL_PERCENTAGE, new QStandardItem());
    this->listModel->setItem(axels->size(), DL_SPEED, new QStandardItem());
    this->listModel->item(axels->size(), DL_NAME)->setText(QString::fromStdString(a->getName()));
    axels->push_back(a);
}
void mainWindow::on_pbStart_clicked(){
    QItemSelectionModel *sm = widget.lstDownloads->selectionModel();
    if (sm->selectedIndexes().size() == 0)
        return;
    QModelIndex qi = sm->selectedRows(0)[0];
    
    this->axels->at(qi.row())->start();
}
void mainWindow::on_pbStop_clicked(){
    QItemSelectionModel *sm = widget.lstDownloads->selectionModel();
    if (sm->selectedIndexes().size() == 0)
        return;
    QModelIndex qi = sm->selectedRows(0)[0];

    this->axels->at(qi.row())->stop();
}
void mainWindow::on_actionSettings_triggered(){
    settingsWindow sw(this->settings);
    sw.setModal(true);
    sw.exec();

    setSettings();
}
void mainWindow::on_actionNew_Download_triggered(){
    bool ok;
    this->startNewDownload(QInputDialog::getText(this, tr("Add new URL"), tr("URL"), QLineEdit::Normal , tr(""), &ok), false);
}
void mainWindow::on_pbAdd_clicked(){
    on_actionNew_Download_triggered();
}
void mainWindow::on_pbRemove_clicked(){
    QItemSelectionModel *sm = widget.lstDownloads->selectionModel();
    if (sm->selectedIndexes().size() == 0)
        return;
    QModelIndex qi = sm->selectedRows(0)[0];
  
    this->axels->at(qi.row())->stop();
    this->axels->erase(this->axels->begin() + qi.row());
    this->listModel->takeRow(qi.row()).clear();
}
void mainWindow::on_actionAbout_triggered(){
    aboutWindow ab;
    ab.setModal(true);
    ab.exec();
}