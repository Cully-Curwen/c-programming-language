#include <ctype.h>
#include <stdio.h>

int getch(void);
void ungetch(int);
void inject(const char *s);      /* inject string into input buffer to allow for testing */
int getint(int *pn);

int main(void) {
    int n, rc;

    inject("42 ");
    rc = getint(&n);
    printf("input \"42 \":   n = %d (expected 42),   rc = %d (expected > 0)\n", n, rc);

    inject("+123 ");
    rc = getint(&n);
    printf("input \"+123 \": n = %d (expected 123),  rc = %d (expected > 0)\n", n, rc);

    inject("-7 ");
    rc = getint(&n);
    printf("input \"-7 \":   n = %d (expected -7),   rc = %d (expected > 0)\n", n, rc);

    inject("+x");
    rc = getint(&n);
    printf("input \"+x\":    rc = %d (expected 0, meaning not a number)\n", rc);
    printf("  next char = '%c' (expected '+')\n", getch());

    inject("-!");
    rc = getint(&n);
    printf("input \"-!\":    rc = %d (expected 0)\n", rc);
    printf("  next char = '%c' (expected '-')\n", getch());

    inject("0 ");
    rc = getint(&n);
    printf("input \"0 \":    n = %d (expected 0),    rc = %d (expected > 0)\n", n, rc);

    return 0;
}

/* getint: get next integer frmo input into *pn */
int getint(int *pn)
{
        int c, sign;

        while (isspace(c = getch()))    /* skip white space */
                ;
        if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
                ungetch(c);     /* it's not a number */
                return 0;
        }
        sign = (c == '-') ? -1 : 1;
        if (c == '+' || c == '-') {
                c = getch();
                if (c != isdigit(c)) {
                        ungetch(c);
                        (sign == -1) ? ungetch('-') : ungetch('+');
                        return 0;
                }
        }
        for (*pn = 0; isdigit(c); c = getch())
                *pn = 10 * *pn + (c - '0');
        *pn *= sign;
        if (c != EOF)
                ungetch(c);
        return c;
}


#define BUFSIZE 100

/* getch / ungetch from K&R §4.3 */
static char buf[BUFSIZE];
static int  bufp = 0;

int getch(void)  {
        return (bufp > 0) ? buf[--bufp] : getchar();
}
void ungetch(int c) {
    if (bufp >= BUFSIZE) printf("ungetch: too many characters\n");
    else buf[bufp++] = c;
}

/* inject a string into the input buffer */
void inject(const char *s)
{
    int len = 0;
    while (s[len]) len++;
    bufp = 0;
    while (len > 0) ungetch(s[--len]);
}
