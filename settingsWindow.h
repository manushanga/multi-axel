/* 
 * File:   settingsWindow.h
 * Author: madura
 *
 * Created on May 12, 2012, 10:57 AM
 */

#ifndef _SETTINGSWINDOW_H
#define	_SETTINGSWINDOW_H

#include "axel.h"
#include "ui_settingsWindow.h"

class settingsWindow : public QDialog {
    Q_OBJECT
public:
    settingsWindow(AxelSettings *s);
    virtual ~settingsWindow();
private:
    Ui::settingsWindow widget;
    AxelSettings *settings;
public slots:
    void on_pbBox_clicked(QAbstractButton *b);
};

#endif	/* _SETTINGSWINDOW_H */
