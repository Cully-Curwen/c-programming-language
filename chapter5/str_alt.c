#include <stdio.h>

void strncpy_(char *, char *, int);
void strncat_(char *, char *, int);
int strncmp_(char *, char *, int);

int main(void)
{
    char s1[100];
    strncpy_(s1, "hello world", 5);
    s1[5] = '\0';
    printf("strncpy_(s, \"hello world\", 5) = \"%s\" (expected \"hello\")\n", s1);

    char s2[100];
    strncpy_(s2, "hi", 5);
    printf("strncpy_(s, \"hi\", 5) = \"%s\" (expected \"hi\")\n", s2);

    char s3[100] = "hello";
    strncat_(s3, " world", 3);
    printf("strncat_(\"hello\", \" world\", 3) = \"%s\" (expected \"hello wo\")\n", s3);

    char s4[100] = "foo";
    strncat_(s4, "bar", 10);
    printf("strncat_(\"foo\", \"bar\", 10) = \"%s\" (expected \"foobar\")\n", s4);

    printf("strncmp_(\"abc\", \"abd\", 2) = %d (expected 0)\n", strncmp_("abc", "abd", 2));
    printf("strncmp_(\"abc\", \"abd\", 3) = %d (expected < 0)\n", strncmp_("abc", "abd", 3));
    printf("strncmp_(\"abd\", \"abc\", 3) = %d (expected > 0)\n", strncmp_("abd", "abc", 3));
    printf("strncmp_(\"abc\", \"abc\", 3) = %d (expected 0)\n", strncmp_("abc", "abc", 3));
    printf("strncmp_(\"abc\", \"abcdef\", 3) = %d (expected 0)\n", strncmp_("abc", "abcdef", 3));
    printf("strncmp_(\"hello\", \"hello\", 0) = %d (expected 0)\n", strncmp_("hello", "hello", 0));

    return 0;
}

void strncpy_(char *s, char *t, int n) {
        int i;
        for (i=0; i < n && *t; i++)
                *s++ = *t++;
        while (i++ < n)
                *s++ = '\0';
}

void strncat_(char *s, char *t, int n) {
        int i;
        while (*s)
                s++;
        for (i = 0; i < n && *t; i++)
                *s++ = *t++;
        while (i++ < n)
                *s++ = '\0';
}

/* strncmp_: compare at most n characters of s and t; return <0 if s < t, 0 if s == t, or >0 if cs > t */
int strncmp_(char *s, char *t, int n) {
        while (*s == *t && *s && n > 0) {
                s++;
                t++;
                n--;
        }
        if (n == 0)
                return 0;
        else
                return (*s < *t) ? -1 : 1;
}

