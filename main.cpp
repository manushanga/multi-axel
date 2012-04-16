/*
 * File:   main.cpp
 * Author: madura
 *
 * Created on April 16, 2012, 8:00 PM
 */

#include <QtGui/QApplication>
#include <mainWindow.h>

int main(int argc, char *argv[]) {
    // initialize resources, if needed
    // Q_INIT_RESOURCE(resfile);

    QApplication app(argc, argv);
    mainWindow w;
    w.show();
    // create and show your widgets here
   
    return app.exec();
}

