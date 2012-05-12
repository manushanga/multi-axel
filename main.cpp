/*
 * File:   main.cpp
 * Author: madura
 *
 * Created on April 16, 2012, 8:00 PM
 */

#include <QtGui/QApplication>
#include <mainWindow.h>
#include <iostream>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;
static void child_handler(int sig){
    pid_t pid;
    int status;

    while((pid = waitpid(-1, &status, WNOHANG)) > 0){
        DPRINT(status);
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

    return app.exec();
}

