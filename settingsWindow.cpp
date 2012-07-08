/*
 * File:   settingsWindow.cpp
 * Author: madura
 *
 * Created on May 12, 2012, 10:57 AM
 */

#include <QAbstractButton>
#include <QSettings>

#include "settingsWindow.h"
#include <iostream>

using namespace std;
void settingsWindow::getSettings(){
    bool ok;
    QSettings qs("MaduraA","MultiAxel");
    qs.beginGroup("Settings");
    this->settings->httpProxy = qs.value("httpProxy").toString().toStdString();
    this->settings->ftpProxy = qs.value("ftpProxy").toString().toStdString();
    this->settings->maxSpeed = qs.value("maxSpeed").toInt(&ok);
    this->settings->numberOfConnections = qs.value("numberOfConnections").toInt(&ok);
    this->settings->userAgent = qs.value("userAgent").toString().toStdString();
    this->settings->workingDirectory = qs.value("workingDirectory").toString().toStdString();        
    qs.endGroup();
}
void settingsWindow::setSettings(){
    QSettings qs("MaduraA","MultiAxel");
    qs.beginGroup("Settings");
    qs.setValue("httpProxy", QVariant(QString().fromStdString(this->settings->httpProxy)));
    qs.setValue("ftpProxy",QVariant(QString().fromStdString(this->settings->ftpProxy)));
    qs.setValue("maxSpeed",QVariant(this->settings->maxSpeed));
    qs.setValue("numberOfConnections", QVariant(this->settings->numberOfConnections));
    qs.setValue("userAgent",QVariant(QString().fromStdString(this->settings->userAgent)));
    qs.setValue("workingDirectory", QVariant(QString().fromStdString(this->settings->workingDirectory)));
    qs.endGroup();
    qs.sync();
}

settingsWindow::settingsWindow() {
    widget.setupUi(this);
    this->settings = new AxelSettings;
    this->getSettings();
    widget.outputDirectoryLineEdit->setText(this->settings->workingDirectory.c_str());
    widget.proxyLineEdit->setText(this->settings->httpProxy.c_str());
    widget.maxSpeedLineEdit->setText(QString("").sprintf("%d",this->settings->maxSpeed));
    widget.maxConnectionsLineEdit->setText(QString("").sprintf("%d",this->settings->numberOfConnections));  
    widget.userAgentLineEdit->setText(this->settings->userAgent.c_str());
}
void settingsWindow::on_pbBox_clicked(QAbstractButton *b) {
    if (widget.pbBox->standardButton(b) == QDialogButtonBox::Ok){
        if (widget.outputDirectoryLineEdit->text().size() > 0 ) {
            this->settings->workingDirectory.assign(widget.outputDirectoryLineEdit->text().toStdString());
        } else {
            this->settings->workingDirectory.assign("");
        }
        
        if (widget.maxSpeedLineEdit->text().size() > 0 ) {
            bool ok;
            int i = widget.maxSpeedLineEdit->text().toInt(&ok, 10);
            if (ok == true)
                this->settings->maxSpeed = i;
            else
                this->settings->maxSpeed = 0;
        } else {
            this->settings->maxSpeed = 0;
        }
        
        if (widget.maxConnectionsLineEdit->text().size() > 0 ) {
            bool ok;
            int i = widget.maxConnectionsLineEdit->text().toInt(&ok, 10);
            if (ok == true)
                this->settings->numberOfConnections = i;
            else
                this->settings->numberOfConnections = 0;
        } else {
            this->settings->numberOfConnections = 0;
        }
        
        if (widget.proxyLineEdit->text().size() > 0 ) {
            this->settings->httpProxy.assign(widget.proxyLineEdit->text().toStdString());
            this->settings->ftpProxy.assign(this->settings->httpProxy.c_str());
        } else {
            this->settings->httpProxy.assign("");
            this->settings->ftpProxy.assign("");
        }
        
        if (widget.userAgentLineEdit->text().size() > 0 ) {
            this->settings->userAgent.assign(widget.userAgentLineEdit->text().toStdString());
        } else {
            this->settings->userAgent.assign("");
        }
        this->setSettings();
    }
    this->close();
}
settingsWindow::~settingsWindow() {
    delete this->settings;
}
 
