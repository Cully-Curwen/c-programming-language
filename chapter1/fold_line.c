#include <stdio.h>

#define MAXLINE 1000            /* maximux line length */
#define COLUMN 40               /* column width to fold on */

int get_line(char s[], int lim);
void copy(char to[], char from[]);
int fold(char s[], int len, int col,  char f[]);

int main(void) {
        int len;

        char line[MAXLINE];
        char folded[COLUMN + 2];

        while ((len = get_line(line, MAXLINE)) > 0) {
                while (len > COLUMN) {
                        len = fold(line, len, COLUMN, folded);
                        printf("%s", folded);
                }
                printf("%s", line);
        }

        return 0;
}

/* get_line: read a line into s, return array length */
int get_line(char s[], int lim) {
        int c, i;

        for (i=0; i<lim-1 && ((c=getchar())!=EOF && c!='\n'); ++i) {
                s[i] = c;
        }
        if (c == '\n') {
                s[i] = c;
                ++i;
        }
        s[i] ='\0';
        return i;
}

/* copy: copy 'from' into 'to'; assume to is big enough */
void copy(char to[], char from[])
{
        int i;

        i = 0;
        while ((to[i] = from [i]) != '\0')
                ++i;
}

/* fold:(recursive) get a line fold on column, returns length of remainder to fold
 * shearches back from column to find first blank or tab to fold on
 * if none adds '-' at column
 * replaces input line with remainder
 */
int fold(char s[], int len, int col, char f[]) {
        int c, i, j, k;
        char r[MAXLINE];

        if (len <= col)
                return len;

        for (i=col; i>0 && ((c=s[i])!=' ' && c!='\t'); --i);

        if (i == 0) {
                for (j = 0; j < col - 1; ++j)
                        f[j] = s[j];

                f[col-1] = '-';
                f[col] = '\n';
                f[col+1] = '\0';

                j = col;
                for (k = 0; k <= len - col; ++k) {
                        r[k] = s[j];
                        ++j;
                }
                r[k] = '\0';

                copy(s, r);
                return len -  col;
        } else {
                for (j = 0; j < i; ++j)
                        f[j] = s[j];

                f[i] = '\n';
                f[i+1] = '\0';

                j = i;
                for (k = 0; k <= len - i; ++k) {
                        r[k] = s[j];
                        ++j;
                }
                r[k] = '\0';

                copy(s, r);
                return len - i;
        }
}
