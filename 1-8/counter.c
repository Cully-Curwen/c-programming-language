#include <stdio.h>

/* count the number of blanks, tabs and new lines */

main()
{
  int c, nb, nt, nl; /* Set number blanks: nb, number tabs: nt, number new lines: nl */

  nb = nt = nl = 0; /* start at zero */
  while((c = getchar()) != EOF) {
    if(c == ' ')
      ++nb;
    if(c =='\t')
      ++nt;
    if(c =='\n')
      ++nl;
  }
  printf("\n\nblanks: %d\ntabs: %d\nnew lines: %d\n", nb, nt, nl);
}
