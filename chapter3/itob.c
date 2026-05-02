#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1000

void itob(int n, char s[], int b);
void reverse(char s[]);

int main(void) {
        char s[MAXLINE];

        itob(255, s, 16);
        printf("itob(255, s, 16) = \"%s\" (expect ff)\n", s);

        itob(255, s, 2);
        printf("itob(255, s, 2) = \"%s\" (expect 11111111)\n", s);

        itob(255, s, 8);
        printf("itob(255, s, 8) = \"%s\" (expect 377)\n", s);

        itob(255, s, 10);
        printf("itob(255, s, 10) = \"%s\" (expect 255)\n", s);

        itob(0, s, 16);
        printf("itob(0, s, 16) = \"%s\" (expect 0)\n", s);

        itob(-1, s, 16);
        printf("itob(-1, s, 16) = \"%s\" (expect -1)\n", s);

        itob(-255, s, 16);
        printf("itob(-255, s, 16) = \"%s\" (expect -ff)\n", s);

        itob(INT_MIN, s, 10);
        printf("itob(INT_MIN, s, 10) = \"%s\" (expect %d)\n", s, INT_MIN);

        itob(INT_MIN, s, 16);
        printf("itob(INT_MIN, s, 16) = \"%s\" (expect -80000000)\n", s);

        itob(42, s, 2);
        printf("itob(42, s, 2) = \"%s\" (expect 101010)\n", s);

        return 0;
}

void itob(int n, char s[], int b) {
        int i, sign, d;

        sign = n;
        i = 0;
        do {
                d = abs(n % b);
                if (d > 9)
                        s[i++] = d - 10 + 'a';
                else
                        s[i++] = d + '0';
        } while ((n /= b) != 0);

        // Not wanted, just to int not encoded for OCT or HEX
        // switch (b) {
        // case 8:
        //         s[i++] = '0';
        //         break;
        // case 16:
        //         s[i++] = 'x';
        //         s[i++] = '0';
        //         break;
        // default:
        //         break;
        // }

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
