/* 
 * File:   Axels.h
 * Author: madura
 *
 * Created on April 17, 2012, 2:47 PM
 */

#ifndef AXELS_H
#define	AXELS_H

#include <string>
#include <vector>

#define DEBUG
#ifdef DEBUG
	#include <iostream>
	#define DPRINT(...) std::cout<<__VA_ARGS__<<endl
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
    string ftpProxy;
    string workingDirectory;
}AxelSettings;

class Axel {
private:
    string url;
    string name;
    pid_t pid;
    string httpProxy;
    string ftpProxy;
    
    vector<string>* args;
    /* read only for other than the reading thread */
    int out_fd;
    state_t state;
    float speed;
    int percentage;
    string workingdir;
    static void *threaded_read(void *obj);
public:
    Axel(string url, AxelSettings& settings);
    void start();
    void stop();
    bool isActive();
    float getSpeed();
    int getPercentage();
    string& getName();
    string& getUrl();
    string getOutput();
    state_t getStatus();
};


#endif	/* AXELS_H */

