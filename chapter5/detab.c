#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1000                 /* maximum length length */
#define TABWIDTH 8
#define TABSTART 0

int get_line(char s[], int lim);
void replace_tab(char *, int len, int tabwidth, int tabstart, int lim);

/* get a line
 * find tabs and replace with blanks
 * blanks equal remainder of tab start column over tab size
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
                replace_tab(line, len, tabwidth, tabstart, MAXLINE);
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
void replace_tab(char *s, int len, int tabwidth, int tabstart, int lim) {
        int col, dif;
        char *sb = s, copy[MAXLINE], *cp = copy, *cpb = cp;


        for (col = 0; *s && col < lim-1; s++) {
                if (*s == '\t' && col >= tabstart) {
                        for (dif = col % tabwidth; dif < tabwidth && col < lim-1; ++dif) {
                                *cp++ = ' ';
                                col++;
                        }
                } else if (*s == '\t') {
                        *cp++ = *s;
                        col += tabwidth - col % tabwidth;
                } else {
                        *cp++ = *s;
                        col++;
                }
        }
        *cp = '\0';

        /* copy replace s */
        while (*cpb)
                *sb++ = *cpb++;
        *sb = '\0';
}
