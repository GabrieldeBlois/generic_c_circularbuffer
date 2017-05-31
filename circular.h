#ifndef CIRCULAR_H_
#define CIRCULAR_H_

#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

typedef struct s_circbuf
{
    unsigned char *buf;
    unsigned int nbcell;
    unsigned int bufsize;
    unsigned int writepos;
    unsigned int readpos;
    unsigned int elesize;
    unsigned char canwrite;
}   t_circbuf;

void circbuf_init(t_circbuf *cb, unsigned int nbcell, unsigned int elesize);
t_circbuf *circbuf_create(unsigned int nbcell, unsigned int elesize);
unsigned int circbuf_write(t_circbuf *cb, void *toput);
unsigned int circbuf_read(t_circbuf *cb, void *dest);

#endif