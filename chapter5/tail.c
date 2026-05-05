#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLINES 10            /* default tail lines to print */
#define MAXLINES 5000           /* max #lines to be sorted */
#define MAXINPUT 10000          /* max input characters stored */

char *lineptr[MAXLINES];        /* pointers to text lines */

int readlines(char *lineptr[], int nlines, char *buf, char *bufend);
void writelines(char *lineptr[], int tlines);

int main(int argc, char *argv[]) {
        int tlines = TAILLINES;

        while (--argc > 0 && **++argv == '-')
                tlines = atoi(*argv+1);

        int nlines;     /* number of input lines read */
        char inputBuff[MAXINPUT];
        char *buf = inputBuff;

        if ((nlines = readlines(lineptr, MAXLINES, buf, buf + MAXINPUT)) >= 0) {
                int lastlines = (tlines > nlines) ? nlines : tlines;
                writelines(lineptr + (nlines - lastlines), lastlines);
                return 0;
        } else {
                printf("error: input too big to sort\n");
                return 1;
        }
}

#define MAXLEN 1000     /* max length of any input line */
int getline_(char *, int);

/* readlinse: read input lines */
int readlines(char *lineptr[], int maxlines, char *buf, char *bufend) {
        int len, nlines;
        char line[MAXLEN];

        nlines = 0;
        while ((len = getline_(line, MAXLEN)) > 0)
                if (nlines >= maxlines || (buf + len) >= bufend) {
                        return -1;
                } else {
                        line[len-1] = '\0';     /* delete newline */
                        strcpy(buf,line);
                        lineptr[nlines++] = buf;
                        buf += len;
                }
        return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int tlines)
{
        while (tlines-- > 0)
                printf("%s\n", *lineptr++);
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

