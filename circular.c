#include "circular.h"

__inline__
void circbuf_free(t_circbuf *cb)
{
    free(cb->buf);
    free(cb);
}

void circbuf_init(t_circbuf *cb, unsigned int nbcell, unsigned int elesize)
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

t_circbuf *circbuf_create(unsigned int nbcell, unsigned int elesize)
{
    t_circbuf *tmp;

    if ((tmp = malloc(sizeof(*tmp))) == NULL)
        return (perror("malloc"), NULL);
    circbuf_init(tmp, nbcell, elesize);
    return (tmp);
}

unsigned int circbuf_write(t_circbuf *cb, void *toput)
{
    if (cb->canwrite)
    {
        memcpy(cb->buf + cb->writepos, toput, cb->elesize);
        cb->writepos += cb->elesize;
        if (cb->writepos == cb->bufsize)
            cb->writepos = 0;
        if (cb->writepos == cb->readpos)
            cb->canwrite = 0;
        return (1);        
    }
    return (0);
}

unsigned int circbuf_read(t_circbuf *cb, void *dest)
{
    if (cb->canwrite == 1 && cb->writepos == cb->readpos)
        return (0);
    memcpy(dest, cb->buf + cb->readpos, cb->elesize);
    cb->readpos += cb->elesize;
    if (cb->readpos == cb->bufsize)
        cb->readpos = 0;
    cb->canwrite = 1;
    return (1);
}

int main()
{
    t_circbuf *tmp;

    tmp = circbuf_create(24, sizeof(int));
    for (int i = 0; i < 30; ++i)
    {
        printf("return: %d for i = %d\n", circbuf_write(tmp, &i), i);
    }
    int c = 0;
    for (int i = 0; i < 30; ++i)
    {
        printf("return: %d for i = %d && a = ", circbuf_read(tmp, &c), i);
        printf("%d\n", c);
    }
    printf("%d\n", *(int *)((char *)tmp->buf + 0));
}