/* 
 * File:   aboutWindow.h
 * Author: madura
 *
 * Created on May 12, 2012, 1:42 PM
 */

#ifndef _ABOUTWINDOW_H
#define	_ABOUTWINDOW_H

#include "ui_aboutWindow.h"

class aboutWindow : public QDialog {
    Q_OBJECT
public:
    aboutWindow();
    virtual ~aboutWindow();
private:
    Ui::About widget;
};

#endif	/* _ABOUTWINDOW_H */
