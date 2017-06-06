#include "circular.h"

void circbuf_free(t_circbuf *cb)
{
    free(cb->buf);
    free(cb);
}

void circbuf_init(t_circbuf *cb, uint32_t nbcell, uint32_t elesize)
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

t_circbuf *circbuf_create(uint32_t nbcell, uint32_t elesize)
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
    cb->readpos = CIRCBUF_FALSE;
  cb->canwrite = CIRCBUF_TRUE;
  return (CIRCBUF_TRUE);
}