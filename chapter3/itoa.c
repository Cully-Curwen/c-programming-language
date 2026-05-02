#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1000

void itoa(int n, char s[]);
void reverse(char s[]);

int main(void) {
        char s[MAXLINE];

        itoa(0, s);
        printf("itoa(0) = \"%s\"\n", s);

        itoa(12345, s);
        printf("itoa(12345) = \"%s\"\n", s);

        itoa(-12345, s);
        printf("itoa(-12345) = \"%s\"\n", s);

        itoa(INT_MAX, s);
        printf("itoa(INT_MAX) = \"%s\" (expect %d)\n", s, INT_MAX);

        itoa(INT_MIN, s);
        printf("itoa(INT_MIN) = \"%s\" (expect %d)\n", s, INT_MIN);

        itoa(-1, s);
        printf("itoa(-1) = \"%s\"\n", s);

        itoa(1, s);
        printf("itoa(1) = \"%s\"\n", s);

        return 0;
}

/* itoa: convert n to characters in a */
void itoa(int n, char s[]) {
        int i, sign;
        int minFlag = 0;

        /* as INT_MIN cannont be reverse and store in INT_MAX
         * so flag and convert to -INT_MAX
         * before signing need to increament by one before being made negative */
        if (n == INT_MIN) {
                minFlag = 1;
                n = -(INT_MIN + 1);
        }
        if ((sign = n) < 0)    /* record sign */
                n = -n;
        i= 0;
        do {            /* genrate digits in reverse order */
                s[i++] = n % 10 + '0';  /* get next digit */
        } while ((n /= 10) > 0);        /* delete it */
        if (minFlag)
                s[0]++;
        if (sign < 0)
                s[i++] = '-';
        s[i] = '\0';
        reverse(s);
}

/* itoa_alt: C99 and later, % and / always truncates to zero */
void itoa_alt(int n, char s[]) {
        int i, sign;

        sign = n;
        i = 0;
        do {
                s[i++] = abs(n % 10) + '0';
        } while ((n /= 10) != 0);
        if (sign < 0)
                s[i++] = '-';
        s[i] = '\0';
        reverse(s);
}

/* reverse: reverse string s in place */
void reverse(char s[]) {
        int c, i, j;

        for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
                c = s[i];
                s[i] = s[j];
                s[j] = c;
        }
}
