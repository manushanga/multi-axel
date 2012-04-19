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
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <algorithm>
using namespace std;
enum state_t{ DOWNLOADING, PAUSED, DONE, ERROR, UNKNOWN, NOMULTI};

typedef struct _AxelSettings{
    int numberOfConnections;
    int maxSpeed;
    string userAgent;
    string httpProxy;
    string outputPath;
}AxelSettings;

class Axel {
private:
    string url;
    pid_t pid;
    string httpProxy;
    int out_fd;
    vector<string>* args;
    state_t state;
    
    /* read only for other than the reading thread */
    float speed;
    int percentage;
    
    static void *threaded_read(void *obj);
    void setSpeed(float s);
    void setPercentage(int p);
public:
    Axel(string url, AxelSettings& settings);
    string getTime();
    void start();
    void stop();
    bool isActive();
    private:

};

class Axels {
public:
    Axels();
    Axels(const Axels& orig);
    vector<Axel>& listAll();
    virtual ~Axels();
private:
    vector<Axel> all;
};

#endif	/* AXELS_H */

