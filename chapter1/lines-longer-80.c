#include <stdio.h>

#define MAXLINE 1000    /* maximum line length */

/* get a line
 * check if it is longer than 80 char
 * print line
 */

int get_line(char s[], int lim);

int main(void)
{

        int len;                /* current line length */
        char line[MAXLINE];     /* current input line */

        while ((len = get_line(line, MAXLINE)) > 0) {
                if (len > 80)
                        printf("length: %d\t%s", len, line);
        }
        return 0;
}

/* get_line: read a line into s, return length */
int get_line(char s[], int lim)
{
        int c, i;

        for (i=0; (c=getchar())!=EOF && c!='\n'; ++i) {
                if (i < lim - 1)
                        s[i] = c;
        }
        if (c == '\n') {
                if (i < lim - 1)
                        s[i] = c;
                ++i;
        }
        if (i < lim - 1)
                s[i] ='\0';
        else
                s[lim - 1] = '\0';
        return i;
}
