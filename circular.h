#ifndef CIRCULAR_H_
#define CIRCULAR_H_

#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>

#define CIRCBUF_TRUE (1)
#define CIRCBUF_FALSE (0)

typedef uint8_t t_circbuf_bool;

typedef struct __attribute__((packed, aligned(8))) s_circbuf
{
  uint8_t* buf;
  uint32_t nbcell;
  uint32_t bufsize;
  uint32_t writepos;
  uint32_t readpos;
  uint32_t elesize;
  uint8_t canwrite;
}   t_circbuf;

void circbuf_init(t_circbuf *cb, uint32_t nbcell, uint32_t elesize);
t_circbuf *circbuf_create(uint32_t nbcell, uint32_t elesize);
t_circbuf_bool circbuf_write(t_circbuf *cb, void *toput);
t_circbuf_bool circbuf_read(t_circbuf *cb, void *dest);

#endif