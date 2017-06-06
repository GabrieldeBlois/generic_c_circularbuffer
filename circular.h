/*
** circular.h for circbuf in /home/gaby/Documents/dev/generic_c_circularbuffer
**
** Made by gaby
** Login   <gabriel.de-blois@epitech.eu>
**
** Started on  Tue Jun  6 19:32:21 2017 gaby
** Last update Tue Jun  6 19:32:23 2017 gaby
*/

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

/*
**   to reduce drastically the size of s_circbuff,
**   the struct has been aligned on 128;;
**   BE CAUTION: this alignement causes the fact that you can't allocate
**   more than (65536) bytes in the circbuff which is
**   equivalent to either 32 cells of 2048 bytes, or 1024 pointers on
**   a 64bits system which is large enough to every common uses of
**   circular buffers...
**
**   TODOLIST:
**   - as s_circbuff is aligned on 128, we can access every
**   struct members with a simple binary OR;
*/

typedef struct __attribute__((packed, aligned(128))) s_circbuf
{
  uint8_t* buf;
  uint16_t nbcell;
  uint16_t bufsize;
  uint16_t writepos;
  uint16_t readpos;
  uint16_t elesize;
  uint8_t canwrite;
}   t_circbuf;

/*
**   sets all the cirbuff variables apropriately
*/

void circbuf_init(t_circbuf *cb, uint16_t nbcell, uint16_t elesize);

/*
**   launches the creation (malloc) of a circbuff and returns it
*/

t_circbuf *circbuf_create(uint16_t nbcell, uint16_t elesize);

/*
**   COPY the content of toputin the circular buffer if it is possible
**   returns CIRCBUFF_TRUE (1) if the write succeeds,
**   CIRCBUF_FALSE (0) otherwise
*/

t_circbuf_bool circbuf_write(t_circbuf *cb, void *toput);

/*
**   COPY the content of the current cell of the circular buffer in
**   the memory space pointed to by dest if it is possible
**   returns CIRCBUFF_TRUE (1) if the read succeeds,
**   CIRCBUF_FALSE (0) otherwise
*/

t_circbuf_bool circbuf_read(t_circbuf *cb, void *dest);

/*
**   frees the circular buffer struct and its buffer.
*/

void circbuf_free(t_circbuf* cb);

#endif
