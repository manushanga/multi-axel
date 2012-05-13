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
#include <QItemSelectionModel>

#include <fstream>
#include <string>

#include "settingsWindow.h"
#include "aboutWindow.h"

#define SETTINGS_FILE "/.multiaxel"

enum cols{DL_NAME=0, DL_STATUS, DL_PERCENTAGE, DL_SPEED};

QString colnames[4] = {"Name", "Status","Percentage","Speed"};
QString statenames[6] = {"Downloading", "Paused", "Done", "Error", 
    "Unknown", "No multi-connections"};
void mainWindow::getSettings(AxelSettingsSave& as){
    as.numberOfConnections = this->settings->numberOfConnections;
    as.maxSpeed = this->settings->maxSpeed;
    strcpy(as.userAgent, this->settings->userAgent.c_str());
    strcpy(as.httpProxy, this->settings->httpProxy.c_str());
    strcpy(as.ftpProxy, this->settings->ftpProxy.c_str());
    strcpy(as.outputPath, this->settings->outputPath.c_str());
    strcpy(as.workingDirectory, this->settings->workingDirectory.c_str());
}
void mainWindow::setSettings(AxelSettingsSave& as){
    this->settings->httpProxy = string(as.httpProxy);
    this->settings->ftpProxy = string(as.ftpProxy);
    this->settings->maxSpeed = as.maxSpeed;
    this->settings->numberOfConnections = as.numberOfConnections;
    this->settings->userAgent =string(as.userAgent);
    this->settings->outputPath = string(as.outputPath);
    this->settings->workingDirectory = string(as.workingDirectory);
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
    string settings_path = string("/home/") + 
        string(getenv("USER")) + string(SETTINGS_FILE) ;
    ifstream s_file( settings_path.c_str() , ios::binary|ios::in);
    axels = new vector<Axel *>;
    this->settings = new AxelSettings;
    DPRINT("Settings "<<settings_path.c_str());
    if (s_file) {
        AxelSettingsSave as;
        s_file.read((char *) &as, sizeof(AxelSettingsSave));
        s_file.close();
        setSettings(as);
        
    } else {
        this->settings->httpProxy = "";
        this->settings->ftpProxy = "";
        this->settings->maxSpeed = 0;
        this->settings->numberOfConnections = 10;
        this->settings->userAgent = "";
        this->settings->outputPath = "";
        this->settings->workingDirectory = string("/home/") + string(getenv("USER")) +string("/Downloads");
        ofstream s_file_w(settings_path.c_str(), ios::binary|ios::out);
        AxelSettingsSave as;
        getSettings(as);
        
        s_file_w.write((char *)&as, sizeof(AxelSettingsSave));
        s_file_w.close();
    }
    s_file.close();
    QRect frect = frameGeometry();
    frect.moveCenter(QDesktopWidget().availableGeometry().center());
    move(frect.topLeft());

    pthread_create(&this->th_updater, NULL, &mainWindow::thread_updater, this);
    *up = true;
}
mainWindow::~mainWindow() {
    pthread_cancel(this->th_updater);
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
void mainWindow::startNewDownload(QString url){
    Axel *a = new Axel(url.toStdString(), *this->settings);
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
    string settings_path = string("/home/") + 
        string(getenv("USER")) + string(SETTINGS_FILE) ;
    
    ofstream s_file_w(settings_path.c_str(), ios::binary|ios::out);
    AxelSettingsSave as;
    getSettings(as);

    s_file_w.write((char *)&as, sizeof(AxelSettingsSave));
    s_file_w.close();
    
}
void mainWindow::on_actionNew_Download_triggered(){
    bool ok;
    this->startNewDownload(QInputDialog::getText(this, tr("Add new URL"), tr("URL"), QLineEdit::Normal , tr(""), &ok));
}
void mainWindow::on_pbAdd_clicked(){
    on_actionNew_Download_triggered();
}
void mainWindow::on_actionAbout_triggered(){
    aboutWindow ab;
    ab.setModal(true);
    ab.exec();
}