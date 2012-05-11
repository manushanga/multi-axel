/*
 * File:   main.cpp
 * Author: madura
 *
 * Created on April 16, 2012, 8:00 PM
 */

#include <QtGui/QApplication>
#include <mainWindow.h>
#include <iostream>
using namespace std;
static void child_handler(int sig){
    pid_t pid;
    int status;

    while((pid = waitpid(-1, &status, WNOHANG)) > 0){
        cout<<"status:"<<status<<" "<<sig<<endl;
    }
}

int main(int argc, char *argv[]) {
    // initialize resources, if needed
    // Q_INIT_RESOURCE(resfile);

    QApplication app(argc, argv);
    mainWindow w;
    w.show();
    
    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = child_handler;
   sigaction(SIGCHLD, &sa, NULL);
/*

    AxelSettings s;
    s.httpProxy = "";
    s.maxSpeed = 0;
    s.numberOfConnections = 10;
    s.userAgent = "";
    s.outputPath = "/home/madura/Downloads/ss.zip";
    char *f="http://www.openworlds.org/data/The.Cove.2009.LIMITED.DVDRip.XviD-AMIABLE/The.Cove.2009.LIMITED.DVDRip.XviD-AMIABLE.avi";
    char *jk="http://joomlacode.org/gf/download/frsrelease/16914/73508/Joomla_2.5.4-Stable-Full_Package.zip";
    Axel *a = new Axel(jk, s);
    a->start();
    while (1) {}
    return 0;*/
    return app.exec();
}

