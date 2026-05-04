#include <ctype.h>
#include <stdio.h>

int atoi(char *);

int main(void)
{
        printf("atoi(\"42\") = %d (expected 42)\n", atoi("42"));
        printf("atoi(\"-7\") = %d (expected -7)\n", atoi("-7"));
        printf("atoi(\"+123\") = %d (expected 123)\n", atoi("+123"));
        printf("atoi(\"0\") = %d (expected 0)\n", atoi("0"));
        printf("atoi(\"  456\") = %d (expected 456)\n", atoi("  456"));
        printf("atoi(\"  -99\") = %d (expected -99)\n", atoi("  -99"));
        printf("atoi(\"\") = %d (expected 0)\n", atoi(""));
        printf("atoi(\"abc\") = %d (expected 0)\n", atoi("abc"));

        return 0;
}

/* atoi: convert s to  integer */
int atoi(char *s) {
        int n;
        int sign = 1;

        while (isspace(*s))
                s++;
        if (*s == '-' || *s == '+')
                sign = (*s++ == '-') ? -1 : 1;  /* increment s to move past sign */
        for (n=0; isdigit(*s); s++)
                n = 10 * n + (*s - '0');

        return n * sign;
}
