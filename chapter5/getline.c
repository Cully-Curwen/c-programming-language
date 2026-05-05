#include <stdio.h>

#define MAXLINE 1000            /* maximun line length */

int getline_(char *, int lim);

int main(void)
{
        char s[100];
        int len;

        printf("Type a line: ");
        len = getline_(s, 100);
        printf("got \"%s\", len = %d\n", s, len);

        printf("Type a line (will truncate to 4): ");
        len = getline_(s, 4);
        printf("got \"%s\", len = %d\n", s, len);

        return 0;
}

/* getline_: get line into s, return length */
int getline_(char *s, int lim) {
        int i, c;

        for (i=0; i<lim && (c=getchar()) &&  c!='\n' && c!=EOF; i++)
                *s++ = c;
        if (c == '\n') {
                *s++ = '\n';
                i++;
        }
        *s = '\0';

        return i;
}

