#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAXLINES 5000           /* max #lines to be sorted */
char *lineptr[MAXLINES];        /* pointers to text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void qsort_(void *lineptr[], int left, int right, int (*comp)(void *, void *), int direction);
int numcmp(const char *, const char *);
int strcmpfold(const char *, const char *);

int (*comp[])(void *, void *) = {
	(int (*)(void *, void *)) strcmp,
	(int (*)(void *, void *)) numcmp,
	(int (*)(void *, void *)) strcmpfold,
};

/* sort input lines */
int main(int argc, char *argv[]) {
        int nlines;             /* number of input lines read */
        int direction = 1;        /* -1 if reverse sort */
        int (*comp)(void *, void *);

        comp = (int (*)(void *, void *))strcmp;
        while (--argc > 0 && **++argv == '-') {
                while (*++*argv) {
                        switch (**argv) {
                        case 'n':
                                comp = (int (*)(void *,void *))numcmp;
                                break;
                        case 'r':
                                direction = -1;
                                break;
                        case 'f':
                                comp = (int (*)(void *, void *))strcmpfold;
                        default:
                                break;
                        }
                }
        }

        if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
                qsort_((void **) lineptr, 0, nlines-1, (int (*)(void*, void*))comp, direction);
                writelines(lineptr, nlines);
                return 0;
        } else {
                printf("input too big to sort\n");
                return 1;
        }
}

#define MAXLEN 1000     /* max length of any input line */
int getline_(char *, int);
char *alloc(int);

/* readlinse: read input lines */
int readlines(char *lineptr[], int maxlines) {
        int len, nlines;
        char *p, line[MAXLEN];

        nlines = 0;
        while ((len = getline_(line, MAXLEN)) > 0)
                if (nlines >= maxlines || (p = alloc(len)) == NULL) {
                        return -1;
                } else {
                        line[len-1] = '\0';     /* delete newline */
                        strcpy(p,line);
                        lineptr[nlines++] = p;
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
void qsort_(void *v[], int left, int right, int (*comp)(void *, void *), int direction) {
        int i, last;
        void swap(void *v[], int, int);

        if (left >= right)      /* do nothing if array contains */
                return;         /* fewer than two elements */
        swap(v, left, (left + right)/2);
        last = left;
        for (i = left+1; i <= right; i++)
                if ((*comp)(v[i], v[left]) * direction < 0)
                        swap(v, ++last, i);
        swap(v, left, last);
        qsort_(v, left, last-1, comp, direction);
        qsort_(v, last+1, right, comp, direction);
}

#include <stdlib.h>

/* numcmp: compare s1 and s2 numerically */
int numcmp(const char *s1, const char *s2) {
        double v1, v2;

        v1 = atof(s1);
        v2 = atof(s2);
        if (v1 < v2)
                return -1;
        else if (v1 > v2)
                return 1;
        else
                return 0;
}

/* strcmpfold: compare s1 and s2 with same case
 * if same, then checks with strcmp so order is standard
 * if s1 > s2 return >0, if s1 < s2 retrun <0
 */
int strcmpfold(const char *s1, const char *s2) {
        const char *s1b = s1, *s2b = s2;
        int result;

        while (*s1 && *s2 && toupper(*s1) == toupper(*s2)) {
                s1++;
                s2++;
        }
        result = toupper(*s1) - toupper(*s2);
        if (result == 0)
                return strcmp(s1b, s2b);
        else
                return result;
}

void swap(void *v[], int i, int j) {
        void *temp;

        temp = v[i];
        v[i] = v[j];
        v[j] = temp;
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

#define ALLOCSIZE 10000         /* size of available space */

static char allocbuf[ALLOCSIZE];        /* storage for alloc */
static char *allocp = allocbuf;          /* next free position */

char *alloc(int n)      /* retun pointer to n characters */
{
        if (allocbuf + ALLOCSIZE - allocp >= n ) {      /* it fits */
                allocp += n;
                return allocp - n;      /* old p */
        } else          /* not enough room */
                return 0;
}

