#include "Axels.h"
#include <sstream>

Axel::Axel(string url, AxelSettings& settings){
    this->url = url;
    stringstream s;
    args = new vector<string>;
    args->push_back("axel");
    //args->push_back("-a");
    if (settings.numberOfConnections != 0) {
        s<<settings.numberOfConnections;
        args->push_back("-n");
        args->push_back(s.str());
    }
    if (settings.maxSpeed != 0) {
        args->push_back("-s");
        s<<settings.maxSpeed;
        args->push_back(s.str());
    }
    if (settings.userAgent.size() != 0) {
        args->push_back("-U");
        args->push_back(settings.userAgent);
    }
    
    if (settings.outputPath.size() != 0) {
        args->push_back("-o");
        args->push_back(settings.outputPath);
    }
    
    args->push_back(url);
   
    if (settings.httpProxy.size() != 0) {
        this->httpProxy = string(settings.httpProxy);
    } else {
        this->httpProxy = string("");
    }
    this->pid = 0;
    this->state = PAUSED;
}
void *Axel::threaded_read(void *obj){
    char d[20]={'\0'};
    char sp[20];
    char status[100];
    string info;
    int rec=0,sp_p=0,status_p=0;
    Axel *ax=(Axel *)obj;
    int rd=read(ax->out_fd, d, 19);
    while (rd>0 && info.find("Starting download",0)==string::npos) {
        info+=d;
        read(ax->out_fd, d, 19);
    }
    if (info.find("Server unsupported",0)!=string::npos) {
        ax->state = NOMULTI;
    }
    while (rd>0) {

        for (int i=0;i<rd;i++){
            if (d[i]=='['){
                rec=1;
                sp_p=0;
                memset(sp,'\0',20);
            } else if (d[i]==']'){
                rec=0;
                if (sp[sp_p-1]=='s') {
                    sp[sp_p-4]='\0';
                    ax->speed = atof(sp);
                } else if (sp[sp_p-1]=='%') {
                    sp[sp_p-1]='\0';
                    ax->percentage= atoi(sp);
                }
            } else if (rec==1){
                sp[sp_p]=d[i];
                sp_p++;
            } else {
                status[status_p]=d[i];
                status_p++;
                if (status_p==100){
                    status_p=0;
                }
            }   
        }

        rd = read(ax->out_fd, d, 19);
    }
    string status_out;
    for (int i=status_p-1;i>=status_p-100;i--){
        if (i<0){
            status_out+=status[i+100];
        }else{
            status_out+=status[i];
        }
    }
    reverse(status_out.begin(), status_out.end());
    if (status_out.find("Unable to connect to server") != string::npos ) {
        ax->state = ERROR;
    } else if (status_out.find("Downloaded") != string::npos ) {
        ax->state = DONE;
    } else {
        ax->state = UNKNOWN;
    }
    return NULL;
}

void Axel::start(){
    if (this->pid == 0) {
        int pipefd[2];
        
        if (pipe(pipefd) == -1)
            perror("Axel::start::pipe");
        
        pid_t pid = fork();
        
        if (pid==0) {
           // dup();
            close(1);
            dup(pipefd[1]);
            close(0);
            
            char* arr[args->size()+1];
            unsigned int i;

            for (i=0;i<args->size();i++) {
                arr[i]=(char *)this->args->at(i).c_str();
            }
            arr[i] = NULL;
            if (this->httpProxy.size() != 0){
                char *env=(char *) string("HTTP_PROXY=").append(this->httpProxy).c_str();
                char* arre[2]= {NULL};
                arre[0] = env;
                execvpe("axel", arr, arre);
            } else {
                execvp("axel", arr);
            }
            perror("Axel::start::execv");
            exit(1);
        } else if (pid>0) {
            this->pid = getpid();
            this->state = DOWNLOADING;
            this->out_fd = pipefd[0];
            
            pthread_t th1;
            pthread_create(&th1, NULL, &Axel::threaded_read, this);
          
        } else {
            perror("Axel::start::fork");
        }
    }
}