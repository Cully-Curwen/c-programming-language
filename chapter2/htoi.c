#include <stdio.h>
#include <string.h>

int htoi(char s[]);

int main (void) {
        printf("%-12s = %d\n", "0xFF", htoi("0xFF"));
        printf("%-12s = %d\n", "0x1A3", htoi("0x1A3"));
        printf("%-12s = %d\n", "0XFF", htoi("0XFF"));
        printf("%-12s = %d\n", "ff", htoi("ff"));
        printf("%-12s = %d\n", "10", htoi("10"));
        printf("%-12s = %d\n", "0", htoi("0"));
        printf("%-12s = %d\n", "0x0", htoi("0x0"));
        printf("%-12s = %d\n", "DEADBEEF", htoi("DEADBEEF"));
        printf("%-12s = %d\n", "0x1f4", htoi("0x1f4"));
        printf("%-12s = %d\n", "hello", htoi("hello"));
        printf("%-12s = %d\n", "0xGG", htoi("0xGG"));
        return 0;
}

int htoi(char s[]) {
        int i, n, c;
        int limit = strlen(s);

        if (limit > 2 && s[0] == '0' && (s[1] == 'x' || s[1] == 'X'))
                i = 2;
        else 
                i = 0;

        for (n = 0; i<limit; ++i, c=-1) {
                if (s[i] >= '0' && s[i] <= '9')
                        c = s[i] - '0';
                if (s[i] >= 'a' && s[i] <= 'f')
                        c = 10 + s[i] - 'a';
                if (s[i] >= 'A' && s[i] <= 'F')
                        c = 10 + s[i] - 'A';

                /* Checks that the string is a valid Hexaidecimal number */
                if (c == -1) {
                        printf("Error: string not a Hexaidecimal number\n"); 
                        return -1;
                }

                n = n * 16 + c;
        }

        return n;
}
