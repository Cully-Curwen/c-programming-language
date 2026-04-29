#include <stdio.h>

#define MAXLINE 1000                 /* maximum length length */
#define TABWIDTH 8

int get_line(char s[], int lim);
void add_tabs(char s[], int len, int tabwidth, int lim);

/* get a line
 * find blacks and replace with tabs
 * print new line
 */
int main(void) {
        int len;
        char line[MAXLINE];

        while ((len = get_line(line, MAXLINE)) > 0) {
                add_tabs(line, len, TABWIDTH, MAXLINE);
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

/* add tabs with blanks
 * count up blank chain,
 * then add max tabs and blanks
 * single blanks not replaced by a tab
 */
void add_tabs(char s[], int len, int tabwidth, int lim) {
        int i, j, c;
        int column, count, tabs, blanks;
        char copy[MAXLINE];

        /* loop through s, when ' ' enter while
         * while ' ' ++blanks, and ++i
         * on exit write tabs and blanks to copy, update j
         * copy char, set blanks to 0
         */
        for (i = j = column = count = 0; i < len; ++i) {
                while (s[i] == ' ' || s[i] == '\t') {
                        if (s[i] == ' ')
                                ++count;
                        else if (s[i] == '\t')
                                count = count + tabwidth;
                        ++i;
                }
                if (count > 1) {
                        for(tabs = column/tabwidth; tabs < (column+count)/tabwidth; ++tabs) {
                                copy[j] = '\t';
                                ++j;
                        }
                        for(blanks = 0; blanks < (column+count)%tabwidth; ++blanks) {
                                copy[j] = ' ';
                                ++j;
                        }
                } else if (count == 1) {
                        copy[j] = ' ';
                        ++j;
                }
                copy[j] = s[i];
                ++j;
                column = column + count + 1;
                count = 0;
        }

        /* copy replace s */
        for (c = 0; c < j && c < lim - 1; ++c)
                s[c] = copy[c];
        s[c] = '\0';
}

