/* 
 * File:   reader.h
 * Author: madura
 *
 * Created on May 13, 2012, 2:52 PM
 */

#ifndef READER_H
#define	READER_H

#ifdef	__cplusplus
extern "C" {
#endif
    #define READER_BUFFER_SIZE 40
    int reader_read(int fd, char *buffer);
#ifdef	__cplusplus
}
#endif

#endif	/* READER_H */

