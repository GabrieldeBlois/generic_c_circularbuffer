#include "circular.h"

int main() {
  t_circbuf* tmp;

  tmp = circbuf_create(24, sizeof(int));
  for (int i = 0; i < 30; ++i) {
    printf("return: %d for i = %d\n", circbuf_write(tmp, &i), i);
  }
  int c = 0;
  for (int i = 0; i < 30; ++i) {
    printf("return: %d for i = %d && a = ", circbuf_read(tmp, &c), i);
    printf("%d\n", c);
  }
  //printf("%d\n", *(int*)((char*)tmp->buf + 0));
  circbuf_free(tmp);
}