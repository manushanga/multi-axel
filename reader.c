#include <unistd.h>
#include <errno.h>
#include "reader.h"
#include <stdio.h>

int reader_read(int fd, char *buffer){
    int rd = read(fd, buffer, READER_BUFFER_SIZE);
    if (rd==-1){
        if (errno == EINTR) 
            return reader_read(fd, buffer);
        else 
            return 0;
    }
    int buffer_wr=rd;

    while (buffer_wr < READER_BUFFER_SIZE && rd>0) {
        rd = read(fd, buffer + buffer_wr, READER_BUFFER_SIZE - buffer_wr);
        if (rd==-1){
            if (errno == EINTR) 
                continue;
            else 
                return 0;
        }
        buffer_wr += rd;
    }
    return buffer_wr;
}