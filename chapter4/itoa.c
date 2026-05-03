#include <limits.h>
#include <stdio.h>
#include <string.h>

#define MAXLINE 1000            /* maximun string length */

void itoa(int n, char s[MAXLINE]);

int main(void) {
        char s[MAXLINE];

        itoa(0, s);
        printf("itoa(0) = \"%s\" (expect \"0\")\n", s);

        itoa(42, s);
        printf("itoa(42) = \"%s\" (expect \"42\")\n", s);

        itoa(-42, s);
        printf("itoa(-42) = \"%s\" (expect \"-42\")\n", s);

        itoa(12345, s);
        printf("itoa(12345) = \"%s\" (expect \"12345\")\n", s);

        itoa(-12345, s);
        printf("itoa(-12345) = \"%s\" (expect \"-12345\")\n", s);

        itoa(7, s);
        printf("itoa(7) = \"%s\" (expect \"7\")\n", s);

        itoa(INT_MAX, s);
        printf("itoa(INT_MAX) = \"%s\" (expect \"%d\")\n", s, INT_MAX);

        itoa(INT_MIN, s);
        printf("itoa(INT_MIN) = \"%s\" (expect \"%d\")\n", s, INT_MIN);

        return 0;
}

int i;

/* itoa_recursive: convert n to string */
void itoa_recursive(int n, char s[MAXLINE]) {
        if (n == INT_MIN) {
                itoa_recursive(n + 1, s);
                s[strlen(s)-1]++;
                return;
        }
        if (n < 0) {
                s[i++] = '-';
                n = -n;
        }
        if (n / 10)
                itoa_recursive(n / 10, s);
        s[i++] = n % 10 + '0';
        s[i] = '\0';

        return;
}

/* itoa: wrapper for itoa_recursive logic */
void itoa(int n, char s[MAXLINE]) {
        i = 0;
        itoa_recursive(n, s);

        return;
}
