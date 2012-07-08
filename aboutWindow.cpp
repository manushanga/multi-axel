/*
 * File:   aboutWindow.cpp
 * Author: madura
 *
 * Created on May 12, 2012, 1:42 PM
 */

#include "aboutWindow.h"

aboutWindow::aboutWindow() {
    widget.setupUi(this);
    QString a;
    a.sprintf("<p align=\"center\">Build date: %s at %s</p>",__DATE__, __TIME__);
    widget.lblCompileDate->setText(a);
}

aboutWindow::~aboutWindow() {
}
