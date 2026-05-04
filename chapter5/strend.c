#include <stdio.h>

int strend(char *, char *);

int main(void)
{
    printf("strend(\"hello world\", \"world\") = %d (expected 1)\n", strend("hello world", "world"));
    printf("strend(\"hello world\", \"hello\") = %d (expected 0)\n", strend("hello world", "hello"));
    printf("strend(\"hello\", \"hello\") = %d (expected 1)\n", strend("hello", "hello"));
    printf("strend(\"hello\", \"\") = %d (expected 1)\n", strend("hello", ""));
    printf("strend(\"\", \"\") = %d (expected 1)\n", strend("", ""));
    printf("strend(\"hi\", \"longer\") = %d (expected 0)\n", strend("hi", "longer"));
    printf("strend(\"abcdef\", \"def\") = %d (expected 1)\n", strend("abcdef", "def"));
    printf("strend(\"abcdef\", \"deg\") = %d (expected 0)\n", strend("abcdef", "deg"));

    return 0;
}

/* strend: returns 1 if t occurs at end of s, otherwise zero */
int strend(char *s, char *t) {
        int i, j;

        for (i=0; *s != '\0'; s++, i++)
                ;
        for (j=0; *t != '\0'; t++, j++)
                ;
        if (j > i)
                return 0;
        for (s -= j, t -= j; *s == *t && *s != '\0'; s++, t++)
                ;
        if (*s == '\0')
                return 1;
        else
                return 0;
}
