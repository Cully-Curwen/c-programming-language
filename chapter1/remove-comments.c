#include <stdio.h>

#define MAXLINE 1000            /* maximux line length */

int get_line(char s[], int lim);
void copy(char to[], char from[]);
void remove_comments(char s[], int len, int lim);

int sFlag, comment = 0;

int main(void) {
        int len;

        char line[MAXLINE];

        while ((len = get_line(line, MAXLINE)) > 0) {
                remove_comments(line, len, MAXLINE);
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

/* remove_comment: take a line, goes through removeing any C comments
 * flags if inside a char or string to not remove non comments
 */
void remove_comments(char s[], int len, int lim) {
        int i, j;
        int cFlag = 0;

        char r[lim];

        for (i = j = 0; i < len; ++i) {
                if (s[i] == '\'' && !sFlag && !comment && s[i-1] != '\\')
                        cFlag = !cFlag;
                if (s[i] == '\"' && !cFlag && !comment && s[i-1] != '\\')
                        sFlag = !sFlag;
                if (s[i] == '*' && s[i-1] == '/' && !cFlag && !sFlag) {
                        comment = 1;
                        --j;
                }
                if (s[i] == '/' && comment && s[i-1] == '*') {
                        comment = 0;
                        ++i;
                }
                if (s[i] == '/' && !comment && !cFlag && !sFlag && s[i-1] == '/') {
                        s[i-1] = '\n';
                        s[i] = '\0';
                        return;
                }

                if (!comment) {
                        r[j] = s[i];
                        ++j;
                }
        }
        r[j] = '\0';

        copy(s, r);
        return;
}

