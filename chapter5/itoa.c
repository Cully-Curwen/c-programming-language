#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void itoa(int, char *);

int main(void)
{
        char s[100];

        itoa(42, s);
        printf("itoa(42) = \"%s\" (expected \"42\")\n", s);

        itoa(-7, s);
        printf("itoa(-7) = \"%s\" (expected \"-7\")\n", s);

        itoa(0, s);
        printf("itoa(0) = \"%s\" (expected \"0\")\n", s);

        itoa(12345, s);
        printf("itoa(12345) = \"%s\" (expected \"12345\")\n", s);

        itoa(-99, s);
        printf("itoa(-99) = \"%s\" (expected \"-99\")\n", s);

        itoa(INT_MIN, s);
        printf("itoa(INT_MIN) = \"%s\" (expected \"%d\")\n", s, INT_MIN);

        return 0;
}

/* itoa: convert n to characters in s */
void itoa(int n, char *s) {
        int temp, digits;

        if (n == INT_MIN) {
                itoa(n+1, s);
                s[strlen(s)-1] += 1;
                return;
        }
        if (n < 0)
                *s++ = '-';

        temp = n;
        digits = 0;
        do
                digits++;
        while (temp /= 10);

        s += digits;

        *s = '\0';
        do
                *--s = abs(n) % 10 + '0';
        while (n /= 10);

}
