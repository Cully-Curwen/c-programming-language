#include <ctype.h>
#include <stdio.h>

#define NUMBER '0'

int getch(void);
void ungetch(int);

/* getop: get next opertator or numeric operand */
int getop(char s[]) {
        static int lastc = 0;
        int i, c;

        if (lastc != 0) {
                c = lastc;
                lastc = 0;
        } else {
                c = getch();
        }

        while (c == ' ' || c == '\t')
                c = getch();
        s[0] = c;
        s[1] = '\0';
        if (!isdigit(c) && c != '.')
                return c;       /* not a number */
        i = 0;
        if (isdigit(c))         /* collect integer part */
                while (isdigit(s[++i] = c = getch()))
                        ;
        if ( c == '.')          /* collect fraction part */
                while (isdigit(s[++i] = c = getch()))
                        ;
        s[i] = '\0';
        if (c != EOF)
                lastc = c;
        return NUMBER;
}
