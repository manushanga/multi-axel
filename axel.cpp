#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <fcntl.h>
#include <sched.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <algorithm>

#include "axel.h"
#include "reader.h"
Axel::Axel(string url, AxelSettings& settings){
    this->url = url;
    args = new vector<string>;
    args->push_back("axel");

    if (settings.numberOfConnections != 0) {
        stringstream s;
        s<<settings.numberOfConnections;
        args->push_back("-n");
        args->push_back(s.str());
    }
    if (settings.maxSpeed != 0) {
        stringstream s;
        args->push_back("-s");
        s<<settings.maxSpeed;
        args->push_back(s.str());
    }
    if (settings.userAgent.size() != 0) {
        args->push_back("-U");
        args->push_back(settings.userAgent);
    }   
    if (settings.header.size() != 0) {
        args->push_back("-H");
        args->push_back(settings.header);
    } 
   
    if (settings.httpProxy.size() != 0) {
        this->httpProxy = string(settings.httpProxy.c_str());
    } else {
        this->httpProxy = string("");
    }
    
    if (settings.workingDirectory.size() != 0) {
        this->workingdir = string(settings.workingDirectory.c_str());
    } else {
        this->workingdir = string("");
    }
    this->speed[0]='0';
    this->speed[1]='\0';
    
    this->pid = 0;
    this->state = AXEL_PAUSED;
    this->percentage = 0;
    size_t p = url.find_last_of('/');
    if (p==string::npos || p==url.length()-1){
        this->name = url;
    } else {
        this->name = url.substr(p+1);
    }
    if (this->name.size() > 254){
        this->name = this->name.substr(0,254);
    }
    args->push_back("-o");
    args->push_back(this->name);
    args->push_back(url);

    DPRINT(this->name);
}
void *Axel::threaded_read(void *obj){
    DPRINT("in threadd");
    char d[READER_BUFFER_SIZE]="";
    char sp[READER_BUFFER_SIZE]="";
    char status[READER_BUFFER_SIZE*3]="";
    string info;
    int rec=0,sp_p=0,status_p=0;
    
    Axel *ax=(Axel *)obj;
    ax->state = AXEL_START;
    
    int rd = reader_read(ax->out_fd, d);
    while (rd> 0 && info.find("Starting download",0)==string::npos) {
        if (rd == -1 && errno == EINTR) {
            perror("Axel::threaded_read::info");
            rd = read(ax->out_fd, d, 1);
            continue;
        }else if (rd==0) 
            break;
        info.append(d, rd);
        rd = reader_read(ax->out_fd, d);
    }
    info.append(d, rd);
    
    int fsize_pos = info.find("File size:",0) +10;
    if (fsize_pos < 0){
        strcpy(ax->filesize,"Not supported.");
    } else {
        strcpy(ax->filesize, info.substr(fsize_pos, info.find("\n", fsize_pos) - fsize_pos).c_str()); 
    }
    
    DPRINT(rd);
    DPRINT(info.c_str());
    
    /* if EOF if hit by now rd==-1 */
    
    if (rd > 0) {
        int bracket_set=0;
        
        if (info.find("Server unsupported",0) != string::npos) {
            ax->state = AXEL_NOMULTI;
        } else {
            ax->state = AXEL_DOWNLOADING;
        }
        rd = reader_read(ax->out_fd, d);
        
        while ( rd>0 ) {
            if (ax->pid == 0) {
                close(ax->out_fd);
                ax->state = AXEL_PAUSED;
                DPRINT("thread exiting");
                return NULL;
            }
            DPRINT(d);
            if (rd==0) 
                break;
            for (int i=0;i<rd;i++){
                if (d[i]=='['){
                    rec=1;
                    sp_p=0;
                    memset(sp,'\0',20);
                    bracket_set++;
                } else if (d[i]==']'){
                    rec=0;
                    if (bracket_set == 1) {
                        strncpy(ax->speed,sp,READER_BUFFER_SIZE);
                        sp[READER_BUFFER_SIZE-1]='\0';  
                    } else if (sp[sp_p-1]=='%') {
                        sp[sp_p-1]='\0';
                        bracket_set=0;
                        ax->percentage= atoi(sp);
                    }
                } else if (rec==1){
                    sp[sp_p]=d[i];
                    sp_p++;
                } else {
                    status[status_p]=d[i];
                    status_p++;
                    if (status_p==READER_BUFFER_SIZE*3){
                        status_p=0;
                    }
                }
            }
            usleep(500);
            rd = reader_read(ax->out_fd, d);
        }
        string status_out;
        for (int i=status_p-1;i>=status_p-(READER_BUFFER_SIZE*3);i--){
            if (i<0){
                status_out+=status[i+READER_BUFFER_SIZE*3];
            }else{
                status_out+=status[i];
            }
        }
        reverse(status_out.begin(), status_out.end());
        if (status_out.find("Downloaded") != string::npos ) {
            ax->percentage = 100;
            ax->state = AXEL_DONE;
        } else {
            ax->state = AXEL_UNKNOWN;
        }
    } else {
        if (info.find("Unable to connect to server") != string::npos ) {
            ax->state = AXEL_NOTFOUND;
        } else {
            ax->state = AXEL_ERROR;
        }
    }
     
    DPRINT("thread exiting");
    DPRINT(ax->state);

    return NULL;
}

void Axel::start(){
    if (this->state == AXEL_DOWNLOADING)
        return;
    
    if (this->pid == 0) {
        int pipefd[2];
        
        if (pipe(pipefd) == -1)
            perror("Axel::start::pipe");
        
        pid_t pid = fork();
        fcntl(pipefd[0], F_SETFL, O_CLOEXEC);
        fcntl(pipefd[1], F_SETFL, O_CLOEXEC);
           
        if (pid == 0) {
            close(1);
            dup(pipefd[1]);
            close(0);
            
            char* arr[args->size()+1];
            unsigned int i;
            
            if (workingdir.size() != 0){
                chdir(workingdir.c_str());
            }
            
            for (i=0;i<args->size();i++) {
                arr[i]=(char *)this->args->at(i).c_str();
                DPRINT(arr[i]);
            }
            arr[i] = NULL;
            string prot = this->url.substr(0, 5);
            std::transform(prot.begin(), prot.end(), prot.begin(), ::tolower);
            if (prot.find("http",0) != string::npos && this->httpProxy.size() != 0  ){
                char env[256];
                sprintf(env,"http_proxy=http://%s", this->httpProxy.c_str());
                char* arre[2];
                arre[0] = env;
                arre[1] = NULL;
                
                execvpe("axel", arr, arre);
            } else if (prot.find("ftp",0) != string::npos && this->ftpProxy.size() != 0  ){
                char env[256];
                sprintf(env,"http_proxy=http://%s", this->httpProxy.c_str());
                char* arre[2];
                arre[0] = env;
                arre[1] = NULL;
                execvpe("axel", arr, arre);
            } else {
                execvp("axel", arr);
            }
            perror("Axel::start::execv");
            exit(1);
        } else if (pid>0) {
            this->pid = pid;
            this->out_fd = pipefd[0];
            close(pipefd[1]);
            waitpid(pid, NULL, WNOHANG);
            pthread_create(&this->th, NULL, &Axel::threaded_read, this);
        } else {
            perror("Axel::start::fork");
        }
    }
}
void Axel::stop(){
    if (this->pid != 0){
        pthread_cancel(this->th);
        close(this->out_fd);
        kill(this->pid, SIGINT);
        this->pid = 0;
        this->state = AXEL_PAUSED;
    }
}
int Axel::getPercentage(){
    return this->percentage;
}
string& Axel::getUrl(){
    return this->url;
}
string Axel::getOutput(){
    return this->workingdir + string("/") + this->name;
}
string& Axel::getName(){
    return this->name;
}
char *Axel::getSpeed(){
    return this->speed;
}
char *Axel::getSize(){
    return this->filesize;
}
state_t Axel::getStatus(){
    return this->state;
}