#include <stdio.h>

#define MAXLINE 1000    /* maximum line length */

/* get a line
 * reverse string
 * print string
 */

int get_line(char s[], int lim);
void reverse_string(char s[], int len, char r[]);

int main(void)
{

        int len;                /* current line length */
        int stored;             /* lenght of stored line */
        char line[MAXLINE];     /* current input line */
        char rev[MAXLINE];

        while ((len = get_line(line, MAXLINE)) > 0) {
                if (len < MAXLINE)
                        stored = len;
                else
                        stored = MAXLINE - 1;
                reverse_string(line, stored, rev);
                printf("%s", rev);
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

/* takes in a string and it length and an ouput string
 * makes output reverse of input string
 * s ends with '\n', '\0' so should copy from len - 2
 */
void reverse_string(char s[], int len, char rev[])
{
        int i;

        for(i=0; i < len - 1; i++) {
                rev[i] = s[len - 2 - i];
        }
        rev[i] = '\n';
        rev[i+1] = '\0';
}

