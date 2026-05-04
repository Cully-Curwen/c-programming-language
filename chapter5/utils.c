#include <stdio.h>

#define BUFSIZE 100
#define NUMBER '0'

/* getch / ungetch from K&R §4.3 */
static char buf[BUFSIZE];
static int  bufp = 0;

int getch(void)  {
        return (bufp > 0) ? buf[--bufp] : getchar();
}
void ungetch(int c) {
    if (bufp >= BUFSIZE) printf("ungetch: too many characters\n");
    else buf[bufp++] = c;
}

/* inject a string into the input buffer */
void inject(const char *s)
{
    int len = 0;
    while (s[len]) len++;
    bufp = 0;
    while (len > 0) ungetch(s[--len]);
}
