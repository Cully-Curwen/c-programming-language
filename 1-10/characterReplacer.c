#include <stdio.h>

main() {
  int c, stop;

  while((c = getchar()) != EOF) {
    stop = 0;
    if(c =='\t') {
      putchar('\\');
      putchar('t');
      stop = 1;
    }
    if(c =='\b') {
      putchar('\\');
      putchar('b');
      stop = 1;
    }
    if(c == '\\') {
      putchar('\\');
      putchar('\\');
      stop = 1;
    }
    if(stop == 0)
      putchar(c);
  }
}
