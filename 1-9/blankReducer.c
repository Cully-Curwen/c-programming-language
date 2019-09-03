#include <stdio.h>

main()
{
  int c, check;

  while((c = getchar()) != EOF) {
    if( c != ' ')
      check = 0;
    if(check != 1)
      putchar(c);
    if(c == ' ')
      check = 1;
  }
}
