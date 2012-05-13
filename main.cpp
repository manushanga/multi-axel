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
    string new_arg;
    tmp >> pid >> new_arg;
    if (main_window_up == true) {
        mw->startNewDownload(QString("").fromStdString(new_arg));
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
            tmpw << pid << " " << argv[1];
            tmpw.close();
        }
        cout << "Another instance detected." << endl;
        exit(0);
    } else {
        tmp.close();
        ofstream tmpw(TMP);
        if (argc > 1){
            tmpw << getpid() << " " << argv[1];
            cout<<"ss"<<endl;
            sleep(1);
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
    
    if (argc>1)
        mw->startNewDownload(QString(argv[1]));
    int ret = app.exec();
    quit_handler(0);
    return ret;
}

