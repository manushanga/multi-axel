/*
 * File:   main.cpp
 * Author: madura
 *
 * Created on April 16, 2012, 8:00 PM
 */
#include <iostream>
#include <fstream>
#include <string>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/inotify.h>

#include <QtGui/QApplication>
#include <QString>

#include <mainWindow.h>
#include "fsevent.h"

#define TMP "/tmp/multiaxel"

fse_watch_t g;
bool main_window_up = false;
mainWindow *mw = NULL;

using namespace std;

static void child_handler(int sig) {
    pid_t pid;
    int status;

    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        DPRINT(status);
    }
}

static void quit_handler(int sig) {
    ifstream tmpd(TMP);
    if (tmpd) {
        pid_t pid;
        string arg;
        tmpd >> pid >> arg;
        tmpd.close();
        fsevent_remove_watch(&g);
        if (pid == getpid()) {
            if (unlink(TMP) == -1)
                cout << "Session file deletion failed, delete manually." << endl;
        }
    }
}

static void fsevent_mod(uint32_t mask) {
    ifstream tmp(TMP);
    pid_t pid;
    string new_arg, new_arg1;
    tmp >> pid >> new_arg;
    QStringList a;

    while (tmp.eof() == false){
        tmp>>new_arg1;
        DPRINT(new_arg1);
        a.append(QString("").fromStdString(new_arg1));      
    }
    if (main_window_up == true) {
        mw->startNewDownload(QString("").fromStdString(new_arg), &a, false);
    }
}

int main(int argc, char *argv[]) {
    // initialize resources, if needed
    // Q_INIT_RESOURCE(resfile);

    QApplication app(argc, argv);
    mainWindow w(&main_window_up);
    mw = &w;
    w.show();

    ifstream tmp(TMP);

    if (tmp) {
        pid_t pid;
        string arg;
        tmp >> pid >> arg;
        tmp.close();

        if (argc > 1) {
            ofstream tmpw(TMP);
            tmpw << pid;
            for (int i=1;i<argc;i++)
                tmpw<< " " << argv[i];
            tmpw.close();
        }
        cout << "Another instance detected." << endl;
        exit(0);
    } else {
        tmp.close();
        ofstream tmpw(TMP);
        if (argc > 1){
            tmpw << getpid();
            for (int i=1;i<argc;i++)
                tmpw<< " " << argv[1];
        } else {
            tmpw << getpid();
        }
        tmpw.close();

        g.callback = fsevent_mod;
        char file[100];
        strcpy(file, TMP);
        g.filename = file;
        g.mask = IN_CLOSE_WRITE;
        fsevent_init(&g);
        fsevent_add_watch(&g);

    }

    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = child_handler;
    sigaction(SIGCHLD, &sa, NULL);

    signal(SIGKILL, quit_handler);
    signal(SIGINT, quit_handler);
    signal(SIGQUIT, quit_handler);
    
    if (argc>1){
        int i=2;
        QStringList a;
        while (i<argc){
            a.append(QString(argv[i]));
            i++;
        }
        mw->startNewDownload(QString(argv[1]), &a, false);
    }
    int ret = app.exec();
    quit_handler(0);
    return ret;
}

