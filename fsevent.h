/* 
 * File:   fsevent.h
 * Author: madura
 *
 * Created on May 12, 2012, 3:52 PM
 */

#ifndef FSEVENT_H
#define	FSEVENT_H

#ifdef	__cplusplus
extern "C" {
#endif
    #include <stdint.h>
    #include <pthread.h>
    
    typedef struct _fse_watch_t{
        int fd;
        pthread_t read_th;
        void (*callback)(uint32_t mask);
        const char *filename;
        uint32_t mask;
    }fse_watch_t;
    
    int fsevent_init(fse_watch_t *fw);
    int fsevent_add_watch(fse_watch_t *fw);
    int fsevent_remove_watch(fse_watch_t *fw);

#ifdef	__cplusplus
}
#endif

#endif	/* FSEVENT_H */

