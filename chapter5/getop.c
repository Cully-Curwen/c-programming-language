#include <ctype.h>
#include <stdio.h>

#include "utils.c"

int getop(char *);

int main(void)
{
        char s[100];
        int type;

        inject("42 ");
        type = getop(s);
        printf("input \"42 \":  type = '%c' (%d), s = \"%s\" (expected type '0' (48), s \"42\")\n", type, type, s);

        inject("3.14 ");
        type = getop(s);
        printf("input \"3.14 \": type = '%c' (%d), s = \"%s\" (expected type '0' (48), s \"3.14\")\n", type, type, s);

        inject("+ ");
        type = getop(s);
        printf("input \"+ \":   type = '%c' (%d) (expected '+' (43))\n", type, type);

        inject("- ");
        type = getop(s);
        printf("input \"- \":   type = '%c' (%d) (expected '-' (45))\n", type, type);

        inject("* ");
        type = getop(s);
        printf("input \"* \":   type = '%c' (%d) (expected '*' (42))\n", type, type);

        inject("/ ");
        type = getop(s);
        printf("input \"/ \":   type = '%c' (%d) (expected '/' (47))\n", type, type);

        inject("\n");
        type = getop(s);
        printf("input \"\\n\":   type = %d (expected '\\n' (10))\n", type);

        return 0;
}

/* getop: get next operator or numeric operand */
int getop(char *s) {
        int c;

        while ((*s = c = getch()) == ' ' || c == '\t')
                ;
        *(s+1) = '\0';
        if (!isdigit(c) && c != '.')
                return c;       /* not a number */
        if (isdigit(c))         /* collect integer part */
                while (isdigit(*++s = c = getch()))
                        ;
        if (c == '.')           /* collect fraction part */
                while (isdigit(*++s = c = getch()))
                        ;
        *s = '\0';
        if (c != EOF)
                ungetch(c);
        return NUMBER;
}
