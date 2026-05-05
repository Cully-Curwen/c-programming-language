#include <stdio.h>
#include <string.h>

#define MAXLINES 5000           /* max #lines to be sorted */
#define MAXINPUT 10000          /* max input characters stored */

char *lineptr[MAXLINES];        /* pointers to text lines */

int readlines(char *lineptr[], int nlines, char *buf, char *bufend);
void writelines(char *lineptr[], int nlines);

void qsort(char *lineptr[], int left, int right);

/* sort input lines */
int main(void) {
        int nlines;     /* number of input lines read */
        char inputBuff[MAXINPUT];
        char *buf = inputBuff;

        if ((nlines = readlines(lineptr, MAXLINES, buf, buf + MAXINPUT)) >= 0) {
                qsort(lineptr, 0, nlines-1);
                writelines(lineptr, nlines);
                return 0;
        } else {
                printf("error: input too big to sort\n");
                return 1;
        }
}

#define MAXLEN 1000     /* max length of any input line */
int getline_(char *, int);
char *alloc(int);

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
void writelines(char *lineptr[], int nlines)
{
        while (nlines-- > 0)
                printf("%s\n", *lineptr++);
}

/* qsort: sort v[left]...v[right] into increasing order */
void qsort(char *v[], int left, int right) {
        int i, last;
        void swap(char *v[], int i, int j);

        if (left >= right)      /* do nothiny if array contains */
                return;         /* fewer than two elements */
        swap(v, left, (left + right)/2);
        last = left;
        for (i = left+1; i <= right; i++)
                if (strcmp(v[i], v[left]) < 0)
                        swap(v, ++last, i);
        swap(v, left, last);
        qsort(v, left, last-1);
        qsort(v, last+1, right);
}

/* swap: interchange v[i] and v[j] */
void swap(char *v[], int i, int j) {
        char *temp;

        temp = v[i];
        v[i] = v[j];
        v[j] = temp;
}

#define ALLOCSIZE 10000                 /* size of available space */

static char allocbuf[ALLOCSIZE];        /* storage for alloc */
static char *allocp = allocbuf;         /* next free position */

char *alloc(int n)      /* return pointer to n characters */
{
        if (allocbuf + ALLOCSIZE - allocp >= n) { /* if it fits */
                allocp += n;
                return allocp - n; /* old p */
        } else          /* not enough room */
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

