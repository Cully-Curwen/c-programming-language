#include <stdio.h>

void reverse(char *);

int main(void)
{
        char s1[] = "hello";
        reverse(s1);
        printf("reverse(\"hello\") = \"%s\" (expected \"olleh\")\n", s1);

        char s2[] = "ab";
        reverse(s2);
        printf("reverse(\"ab\") = \"%s\" (expected \"ba\")\n", s2);

        char s3[] = "a";
        reverse(s3);
        printf("reverse(\"a\") = \"%s\" (expected \"a\")\n", s3);

        char s4[] = "";
        reverse(s4);
        printf("reverse(\"\") = \"%s\" (expected \"\")\n", s4);

        char s5[] = "abcdef";
        reverse(s5);
        printf("reverse(\"abcdef\") = \"%s\" (expected \"fedcba\")\n", s5);

        return 0;
}

/* reverse: reverse string s in place */
void reverse(char *s) {
        char c;
        char *t = s;

        while (*t)
                t++;

        t--;
        while (s < t) {
                c = *s;
                *s++ = *t;
                *t-- = c;
        }
}
