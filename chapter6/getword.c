#include <stdio.h>
#include <ctype.h>

/* getword: get next word or character from input */
int getword(char *word, int lim) {
        int c, getch(void);
        void ungetch(int);
        char *w = word;

        while (isspace(c = getch()))
                ;
        if (c != EOF)
                *w++ = c;
        if (c == '\\')
                c = getch();
        if (c == '"') {
                while ((c = getch()) != EOF) {
                        if (c == '\\')
                                getch();
                        else if (c == '"')
                                break;
                }
        }
        if (c == '#')
                while ((c = getch()) != EOF)
                        if (c == '\n')
                                break;
        if (c == '/') {
                if ((c = getch()) == '*')
                       while ((c = getch()) != EOF) {
                               if (c == '*' && (c = getch()) == '/')
                                       break;
                       }
                else {
                        ungetch(c);
                        c = '/';
                }
        }
        if (!isalpha(c) && c != '_') {
                *w = '\0';
                return c;
        }
        for ( ; --lim > 0; w++)
                if (!isalnum(*w = getch()) && *w != '_') {
                        ungetch(*w);
                        break;

                } 
        *w = '\0';
        return word[0];
}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
        return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
        if (bufp >= BUFSIZE)
                printf("ungetch: too many characters\n");
        else
                buf[bufp++] = c;
}
