/*
 * File:   settingsWindow.cpp
 * Author: madura
 *
 * Created on May 12, 2012, 10:57 AM
 */

#include <qt4/QtGui/qabstractbutton.h>

#include "settingsWindow.h"
#include <iostream>
using namespace std;
settingsWindow::settingsWindow(AxelSettings *s) {
    widget.setupUi(this);
    this->settings = s;
    widget.outputDirectoryLineEdit->setText(QString(s->workingDirectory.c_str()));
    widget.proxyLineEdit->setText(QString(s->httpProxy.c_str()));
    widget.maxSpeedLineEdit->setText(QString("").setNum(s->maxSpeed,10));
    widget.maxConnectionsLineEdit->setText(QString("").setNum(s->numberOfConnections,10));  
    widget.userAgentLineEdit->setText(QString(s->userAgent.c_str()));
}
void settingsWindow::on_pbBox_clicked(QAbstractButton *b) {
    if (widget.pbBox->standardButton(b) == QDialogButtonBox::Ok){
        if (widget.outputDirectoryLineEdit->text().size() > 0 ) {
            this->settings->workingDirectory = widget.outputDirectoryLineEdit->text().toStdString();
        } else {
            this->settings->workingDirectory = string("");
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
            this->settings->httpProxy = widget.proxyLineEdit->text().toStdString();
            this->settings->ftpProxy = string(this->settings->httpProxy);
        } else {
            this->settings->httpProxy = string("");
            this->settings->ftpProxy = string("");
        }
        
        if (widget.userAgentLineEdit->text().size() > 0 ) {
            this->settings->userAgent = widget.userAgentLineEdit->text().toStdString();
        } else {
            this->settings->userAgent = string("");
        }
    }
    this->close();
}
settingsWindow::~settingsWindow() {
}
