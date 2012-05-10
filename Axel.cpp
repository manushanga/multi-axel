#include "Axels.h"
#include <syscall.h>

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
    this->state = AXEL_PAUSED;
    this->speed = 0.0f;
    this->percentage = 0;
    size_t p = url.find_last_of('/');
    if (p==string::npos || p==url.length()-1){
        this->name = url;
    } else {
        this->name = url.substr(p+1);
    }
}
int threaded_read(void *obj){
    DPRINT("in threadd");
    char d[20]={'\0'};
    char sp[20];
    char status[100];
    string info;
    int rec=0,sp_p=0,status_p=0;
    Axel *ax=(Axel *)obj;
    DPRINT("fd%d\n", ax->out_fd);
    int rd=read(ax->out_fd, d, 19);
    if (rd==-1)
        perror("Axel::threaded_read");
    while (rd==19 && info.find("Starting download",0)==string::npos) {
        info.append(d, rd);
        DPRINT("%d\n",rd);
        rd=read(ax->out_fd, d, 19);
        if (rd == -1 && errno == EINTR) {
            perror("xx");
    
            rd=read(ax->out_fd, d, 19);
            continue;
        }
    }
    info.append(d, rd);
    DPRINT("%d\n",rd);
    DPRINT("dd\n");
    DPRINT("%s",info.c_str());
    DPRINT("\n");
    /* if EOF if hit by now rd==-1 */
    
    if (rd==19) {
        rd=read(ax->out_fd, d, 19);

        while (rd==19) {
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
        cout<<status_out<<endl;
        if (status_out.find("Downloaded") != string::npos ) {
            ax->state = AXEL_DONE;
        } else {
            ax->state = AXEL_UNKNOWN;
        }
    } else {
        if (info.find("Server unsupported",0)!=string::npos) {
            ax->state = AXEL_NOMULTI;
        } else if (info.find("Unable to connect to server") != string::npos ) {
            ax->state = AXEL_ERROR;
            
        }
    }
     
    DPRINT("thread exiting");
    DPRINT("%d\n",ax->state);

    return 0;
}

void Axel::start(){
    if (this->pid == 0) {
        int pipefd[2];
        
        if (pipe(pipefd) == -1)
            perror("Axel::start::pipe");
        
        pid_t pid = fork();
        fcntl(pipefd[0], F_SETFL, O_CLOEXEC);
        fcntl(pipefd[1], F_SETFL, O_CLOEXEC);
           
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
            this->pid = pid;
            this->state = AXEL_DOWNLOADING;
            this->out_fd = pipefd[0];
            
           // waitpid(pid, NULL,WNOHANG);
            cout<<pid<<endl;
            //pthread_t th1;
            void *stack_space = malloc(100);
            //pthread_create(&th1, NULL, &Axel::threaded_read, this);
           // clone(threaded_read, (void *)((char *)stack_space+99),  CLONE_FILES|CLONE_FS|CLONE_IO, this ) ;
         //  pthread_join(th1, NULL);
           threaded_read(this);
        } else {
            perror("Axel::start::fork");
        }
    }
}
void Axel::stop(){
    cout<<this->pid<<endl;
    close(this->out_fd);
    kill(this->pid, SIGTERM);
}
int Axel::getPercentage(){
    return this->percentage;
}

string& Axel::getName(){
    return this->name;
}
float Axel::getSpeed(){
    return this->speed;
}
state_t Axel::getStatus(){
    return this->state;
}