#include <stdio.h>

#define MAXLINE 1000            /* maximux line length */

int get_line(char s[], int lim);
void copy(char to[], char from[]);
void open_counter(char s[], int len);

int sFlag = 0, comment = 0;
int par, brk, brc = 0;          /* count of open parentheses, brackets and braces */

int main(void) {
        int len;

        char line[MAXLINE];

        while ((len = get_line(line, MAXLINE)) > 0) {
                open_counter(line, len);
        }

        if (par > 0)
                printf("Error: %d Parentheses are not matched", par);
        if (brk > 0)
                printf("Error: %d Brackets are not matched", brk);
        if (brc > 0)
                printf("Error: %d Braces are not matched", brc);

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

/* opent_counter: take a line, adjusts global count of open parentheses, brackets and braces
 * flags if inside a char, string or comment
 */
void open_counter(char s[], int len) {
        int i;
        int cFlag = 0;

        for (i = 0; i < len; ++i) {
                // flags
                if ((cFlag || sFlag) && s[i] == '\\') {
                        ++i;
                        continue;
                }
                if (s[i] == '\'' && !sFlag && !comment)
                        cFlag = !cFlag;
                if (s[i] == '\"' && !cFlag && !comment)
                        sFlag = !sFlag;
                if (s[i] == '*' && (i > 0 && s[i-1] == '/') && !cFlag && !sFlag)
                        comment = 1;
                if (s[i] == '/' && comment && (i > 0 && s[i-1] == '*'))
                        comment = 0;
                if (s[i] == '/' && !comment && !cFlag && !sFlag && (i > 0 && s[i-1] == '/')) {
                        return;
                }

                // counter
                if (!comment && !sFlag && !cFlag) {
                        if (s[i] == '(')
                                ++par;
                        if (s[i] == ')' && par > 0)
                                --par;
                        if (s[i] == '[')
                                ++brk;
                        if (s[i] == ']' && brk > 0)
                                --brk;
                        if (s[i] == '{')
                                ++brc;
                        if (s[i] == '}' && brc > 0)
                                --brc;
                }
        }

        return;
}

