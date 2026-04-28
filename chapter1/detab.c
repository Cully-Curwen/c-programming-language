#include <stdio.h>

#define MAXLINE 1000                 /* maximum length length */
#define TABWIDTH 8

int get_line(char s[], int lim);
void replace_tab(char s[], int len, int tabwidth, int lim);

/* get a line
 * find tabs and replace with blanks
 * blanks equal remainder of tab start column over tab size
 * print new line
 */
int main(void) {
        int len;
        char line[MAXLINE];

        while ((len = get_line(line, MAXLINE)) > 0) {
                replace_tab(line, len, TABWIDTH, MAXLINE);
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

/* replace tabs with blanks */
void replace_tab(char s[], int len, int tabwidth, int lim) {
        int i, j, c;
        char copy[MAXLINE];

        for (i = j = 0; i < len && j < lim - 1; ++i) {
                if (s[i] == '\t') {
                        for (int dif = j % tabwidth; dif < tabwidth && j < lim - 1; ++dif) {
                                copy[j] = ' ';
                                ++j;
                        }
                } else {
                        copy[j] = s[i];
                        ++j;
                }
        }

        /* copy replace s */
        for (c = 0; c < j && c < lim - 1; ++c)
                s[c] = copy[c];
        s[c] = '\0';
}
