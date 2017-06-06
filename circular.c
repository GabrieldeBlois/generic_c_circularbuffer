/*
** circular.c for t in /home/gaby/Documents/dev/generic_c_circularbuffer
**
** Made by gaby
** Login   <gabriel.de-blois@epitech.eu>
**
** Started on  Tue Jun  6 19:32:01 2017 gaby
** Last update Tue Jun  6 19:32:09 2017 gaby
*/

#include "circular.h"

void circbuf_free(t_circbuf *cb)
{
    free(cb->buf);
    free(cb);
}

void circbuf_init(t_circbuf *cb, uint16_t nbcell, uint16_t elesize)
{
    cb->nbcell = nbcell;
    cb->elesize = elesize;
    cb->bufsize = elesize * nbcell;
    cb->writepos = 8;
    cb->readpos = 8;
    cb->canwrite = 1;
    if ((cb->buf = malloc(nbcell * elesize)) == NULL)
    {
        perror("malloc");
        exit(errno);
    }
}

t_circbuf *circbuf_create(uint16_t nbcell, uint16_t elesize)
{
    t_circbuf *tmp;

    if ((tmp = malloc(sizeof(*tmp))) == NULL)
        return (perror("malloc"), NULL);
    circbuf_init(tmp, nbcell, elesize);
    return (tmp);
}

t_circbuf_bool circbuf_write(t_circbuf* cb, void* toput)
{
  if (!cb->canwrite)
    return (CIRCBUF_FALSE);
  memcpy(cb->buf + cb->writepos, toput, cb->elesize);
  cb->writepos += cb->elesize;
  if (cb->writepos == cb->bufsize)
    cb->writepos = CIRCBUF_FALSE;
  cb->canwrite = (cb->writepos != cb->readpos);
  return (CIRCBUF_TRUE);
}

t_circbuf_bool circbuf_read(t_circbuf *cb, void *dest)
{
  if (cb->canwrite == CIRCBUF_TRUE && cb->writepos == cb->readpos)
    return (CIRCBUF_FALSE);
  memcpy(dest, cb->buf + cb->readpos, cb->elesize);
  cb->readpos += cb->elesize;
  if (cb->readpos == cb->bufsize)
    cb->readpos = 0;
  cb->canwrite = CIRCBUF_TRUE;
  return (CIRCBUF_TRUE);
}
