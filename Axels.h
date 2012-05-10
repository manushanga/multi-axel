/* 
 * File:   Axels.h
 * Author: madura
 *
 * Created on April 17, 2012, 2:47 PM
 */

#ifndef AXELS_H
#define	AXELS_H

#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <pthread.h>
#include <string.h>
#include <algorithm>
#include <sstream>
#include <fcntl.h>
#include <sched.h>
#include <errno.h>

#define DEBUG
#ifdef DEBUG
	#include <stdio.h>
	#define DPRINT(...) fprintf(stderr, __VA_ARGS__)
#else
	#define DPRINT(...) 
#endif

using namespace std;
enum state_t{ AXEL_DOWNLOADING=0, AXEL_PAUSED, AXEL_DONE, AXEL_ERROR, AXEL_UNKNOWN, AXEL_NOMULTI };

typedef struct _AxelSettings{
    int numberOfConnections;
    int maxSpeed;
    string userAgent;
    string httpProxy;
    string outputPath;
}AxelSettings;

int threaded_read(void *obj);

class Axel {
private:
    string url;
    string name;
    pid_t pid;
    string httpProxy;
    
    vector<string>* args;
    
    
    /* read only for other than the reading thread */
    
    
    
public:
    int out_fd;
    state_t state;
    float speed;
    int percentage;
    Axel(string url, AxelSettings& settings);
    void start();
    void stop();
    bool isActive();
    float getSpeed();
    int getPercentage();
    string& getName();
    state_t getStatus();
};


#endif	/* AXELS_H */

