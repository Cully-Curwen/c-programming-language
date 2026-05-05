#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1000                 /* maximum length length */
#define TABWIDTH 8
#define TABSTART 0

int get_line(char s[], int lim);
void add_tabs(char *s, int len, int tabwidth, int tabstart, int lim);

/* get a line
 * find blacks and replace with tabs
 * print new line
 */
int main(int argc, char *argv[]) {
        int len;
        char line[MAXLINE];
        int tabwidth = TABWIDTH;
        int tabstart = TABSTART;

        while (--argc > 0) {
                switch (**++argv) {
                case '-':
                        if (isdigit(*++*argv)) {
                                tabstart = atoi(*argv);
                        } else {
                                printf("entab: illegal option %c", **argv);
                                return -1;
                        }
                        break;
                case '+':
                        if (isdigit(*++*argv)) {
                                tabwidth = atoi(*argv);
                        } else {
                                printf("entab: illegal option %c", **argv);
                                return -1;
                        }
                        break;
                default:
                        if (isdigit(**argv)) {
                                tabwidth = atoi(*argv);
                        } else {
                                printf("entab: illegal option %c", **argv);
                                return -1;
                        }
                        break;
                }
        }

        while ((len = get_line(line, MAXLINE)) > 0) {
                add_tabs(line, len, tabwidth, tabstart, MAXLINE);
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
void add_tabs(char *s, int len, int tabwidth, int tabstart, int lim) {
        int col = 0, dif = 0;
        int tabs, blanks;
        char *sb = s;
        char copy[MAXLINE], *cp = copy, *cpb = cp;

        /* loop through s, when ' ' enter while
         * while ' ' ++blanks, and ++i
         * on exit write tabs and blanks to copy, update j
         * copy char, set blanks to 0
         */
        while (*s) {
                for (dif = 0; col >= tabstart && (*s == ' ' || *s == '\t'); s++) {
                        if (*s == ' ') {
                                dif++;
                        }
                        if (*s == '\t') {
                                dif += tabwidth - (col + dif) % tabwidth;
                        }
                }
                int target = col + dif;
                if (dif > 1) {
                        for(tabs = col / tabwidth; tabs < target / tabwidth; ++tabs) {
                                *cp++ = '\t';
                                col += tabwidth - col % tabwidth;
                        }
                        for(blanks = 0; blanks < target % tabwidth; ++blanks) {
                                *cp++ = ' ';
                                col++;
                        }
                } else if (dif == 1) {
                        *cp++ = ' ';
                        col++;
                }
                if (*s) {
                        *cp++ = *s;
                        col++;
                        s++;
                }
        }
        *cp = '\0';

        /* copy replace s */
        while (*cpb)
                *sb++ = *cpb++;
        *sb = '\0';
}

