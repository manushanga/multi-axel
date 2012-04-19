/*
 * File:   main.cpp
 * Author: madura
 *
 * Created on April 16, 2012, 8:00 PM
 */

#include <QtGui/QApplication>
#include <mainWindow.h>
#include <Axels.h>

int main(int argc, char *argv[]) {
    // initialize resources, if needed
    // Q_INIT_RESOURCE(resfile);

    QApplication app(argc, argv);
    mainWindow w;
    w.show();
    // create and show your widgets here
    AxelSettings s;
    s.httpProxy = "";
    s.maxSpeed = 0;
    s.numberOfConnections = 10;
    s.userAgent = "";
    s.outputPath = "/home/madura/Downloads/ss.zip";
    char *f="http://www.openworlds.org/data/The.Cove.2009.LIMITED.DVDRip.XviD-AMIABLE/The.Cove.2009.LIMITED.DVDRip.XviD-AMIABLE.avi";
    char *jk="http://joomlacode.org/gf/download/frsrelease/16914/73508/Joomla_2.5.4-Stable-Full_Package.zip";
    Axel a(jk, s);
    a.start();

    return app.exec();
}

