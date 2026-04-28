#include <stdio.h>

#define MAXLINE 1000    /* maximum line length */

/* get a line
 * remove trailing blankspace or tabs
 * print line if longer than 1 (no '\n')
 */

int get_line(char s[], int lim);
int remove_blanks(char s[], int len);

int main(void)
{

        int len;                /* current line length */
        char line[MAXLINE];     /* current input line */

        while ((len = get_line(line, MAXLINE)) > 0) {
                len = remove_blanks(line, (len < MAXLINE ? len : MAXLINE));
                if (len > 0)
                        printf("%s", line);
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

/* remove trailing blanks and tabs */
/* length is to \n does not inclued \0, so represent the index of \0 */
/* returns length of no blanks sting */
int remove_blanks(char s[], int len)
{
        int i;

        for (i=len; i>=0 && (s[i]=='\n' || s[i]=='\0' || s[i]=='\t' || s[i]==' '); i--);
        s[i+1] = '\n';
        s[i+2] = '\0';
        return i;
}
