#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1000

void itoa(int n, char s[], int w);
void reverse(char s[]);

int main(void) {
        char s[MAXLINE];

        itoa(42, s, 10);
        printf("|%s| (expect |        42|)\n", s);

        itoa(-42, s, 10);
        printf("|%s| (expect |       -42|)\n", s);

        itoa(0, s, 5);
        printf("|%s| (expect |    0|)\n", s);

        itoa(12345, s, 5);
        printf("|%s| (expect |12345|)\n", s);

        itoa(12345, s, 3);
        printf("|%s| (expect |12345|)\n", s);

        itoa(INT_MIN, s, 15);
        printf("|%s| (expect |   -2147483648|)\n", s);

        itoa(INT_MAX, s, 15);
        printf("|%s| (expect |    2147483647|)\n", s);

        itoa(7, s, 1);
        printf("|%s| (expect |7|)\n", s);

        return 0;
}

/* itoa: convert n to characters in a, width minimum field with w */
void itoa(int n, char s[], int w) {
        int i, sign;

        sign = n;
        i = 0;
        do {
                s[i++] = abs(n % 10) + '0';
        } while ((n /= 10) != 0);
        if (sign < 0)
                s[i++] = '-';
        while (i < w)
                s[i++] = ' ';
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
