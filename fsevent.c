#include "fsevent.h"
#include <poll.h>
#include <unistd.h>
#include <sys/inotify.h>
#include <stdio.h>

int fsevent_init(fse_watch_t *fw){
    int fd = inotify_init();
    if (fd==-1) {
        return -1;
    }
    fw->fd = fd;
    return 0;
}
void *read_thread(void *arg){
    fse_watch_t *fw = (fse_watch_t *) arg;
    struct inotify_event ie;
    struct pollfd pfd;
    
    pfd.fd = fw->fd;
    pfd.events = POLLIN;
    pfd.revents = 0;
 
    while (poll(&pfd, 1, -1)) {
        read(fw->fd, (void *) &ie, sizeof(struct inotify_event));
        printf("%d" ,ie.wd);
        fw->callback(ie.mask);
    }
    return NULL;
}
int fsevent_add_watch(fse_watch_t *fw) {
    if (inotify_add_watch(fw->fd,fw->filename,fw->mask)==-1){
        return -1;
    }
    return pthread_create(&fw->read_th, NULL, read_thread, (void *)fw);
}

int fsevent_remove_watch(fse_watch_t *fw) {
    return pthread_cancel(fw->read_th);
}