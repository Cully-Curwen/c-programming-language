#include <ctype.h>
#include <stdio.h>

int getch(void);
void ungetch(int);
void inject(const char *s);      /* inject string into input buffer to allow for testing */
int getfloat(double *pn);

int main(void)
{
    double v;
    int rc;

    inject("3.14 ");
    rc = getfloat(&v);
    printf("input \"3.14 \":   v = %f (expected 3.140000),  rc = %d (expected > 0)\n", v, rc);

    inject("-0.5 ");
    rc = getfloat(&v);
    printf("input \"-0.5 \":   v = %f (expected -0.500000), rc = %d (expected > 0)\n", v, rc);

    inject("+123.456 ");
    rc = getfloat(&v);
    printf("input \"+123.456 \": v = %f (expected 123.456000), rc = %d (expected > 0)\n", v, rc);

    inject("42 ");
    rc = getfloat(&v);
    printf("input \"42 \":     v = %f (expected 42.000000), rc = %d (expected > 0)\n", v, rc);

    inject(".75 ");
    rc = getfloat(&v);
    printf("input \".75 \":    v = %f (expected 0.750000),  rc = %d (expected > 0)\n", v, rc);

    inject("0 ");
    rc = getfloat(&v);
    printf("input \"0 \":      v = %f (expected 0.000000),  rc = %d (expected > 0)\n", v, rc);

    inject("+x");
    rc = getfloat(&v);
    printf("input \"+x\":      rc = %d (expected 0)\n", rc);

    inject("-!");
    rc = getfloat(&v);
    printf("input \"-!\":      rc = %d (expected 0)\n", rc);

    return 0;
}

/* getfloat: get next double from input into *pn */
int getfloat(double *pn)
{
        double c, power, sign;

        while (isspace(c = getch()))    /* skip white space */
                ;
        if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.') {
                ungetch(c);     /* it's not a number */
                return 0;
        }
        sign = (c == '-') ? -1.0 : 1.0;
        if (c == '+' || c == '-') {
                c = getch();
                if (!isdigit(c)) {
                        ungetch(c);
                        (sign == -1) ? ungetch('-') : ungetch('+');
                        return 0;
                }
        }
        for (*pn = 0.0; isdigit(c); c = getch())
                *pn = 10.0 * *pn + (c - '0');
        if (c == '.')
            c = getch();
        for (power = 1.0; isdigit(c); c = getch()) {
                power *= 10.0;
                *pn = 10.0 * *pn + (c - '0');
        }
        *pn = (*pn / power) * sign;
        if (c != EOF)
                ungetch(c);
        return (int)c;
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

