#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAXLINES 5000           /* max #lines to be sorted */
char *lineptr[MAXLINES];        /* pointers to text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void qsort_(void *lineptr[], int left, int right, int (*comp)(void *, void *));
int numcmp(const char *, const char *);
int strcmp_flags(const char *, const char *);

int direction = 1;      /* -1 if reverse sort */
int fcase = 0;          /* 1 if fold upper and lower case */
int dcase = 0;          /* 1 if directory order */

/* sort input lines */
int main(int argc, char *argv[]) {
        int nlines;             /* number of input lines read */
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
                                comp = (int (*)(void *, void *))strcmp_flags;
                                fcase = 1;
                                break;
                        case 'd':
                                comp = (int (*)(void *, void *))strcmp_flags;
                                dcase = 1;
                                break;
                        default:
                                break;
                        }
                }
        }

        if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
                qsort_((void **) lineptr, 0, nlines-1, (int (*)(void*, void*))comp);
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
void qsort_(void *v[], int left, int right, int (*comp)(void *, void *)) {
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
        qsort_(v, left, last-1, comp);
        qsort_(v, last+1, right, comp);
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

/* strcmp_flags: compare s1 and s2
 * with fcase flag fold upper and lower case
 * with dcase only compare blanks, numbers, letters
 * if same, then checks with strcmp so order is standard
 * if s1 > s2 return >0, if s1 < s2 retrun <0
 */
int strcmp_flags(const char *s1, const char *s2) {
        const char *s1b = s1, *s2b = s2;
        int result;

        while (*s1 && *s2) {
                while (dcase && *s1 && !isspace(*s1) && !isalnum(*s1))
                        s1++;
                while (dcase && *s2 && !isspace(*s2) && !isalnum(*s2))
                        s2++;

                if (fcase && toupper(*s1) != toupper(*s2))
                        break;
                else if (!fcase && *s1 != *s2)
                        break;
                else if (!*s1 || !*s2)
                        break;
                s1++;
                s2++;
        }

        result = (fcase) ? toupper(*s1) - toupper(*s2) : *s1 - *s2;
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

