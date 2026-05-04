#include <stdio.h>

void strcat_(char *, char *);

int main(void)
{
    char s1[100] = "hello";
    strcat_(s1, " world");
    printf("\"hello\" + \" world\" = \"%s\" (expected \"hello world\")\n", s1);

    char s2[100] = "";
    strcat_(s2, "abc");
    printf("\"\" + \"abc\" = \"%s\" (expected \"abc\")\n", s2);

    char s3[100] = "abc";
    strcat_(s3, "");
    printf("\"abc\" + \"\" = \"%s\" (expected \"abc\")\n", s3);

    char s4[100] = "";
    strcat_(s4, "");
    printf("\"\" + \"\" = \"%s\" (expected \"\")\n", s4);

    char s5[100] = "foo";
    strcat_(s5, "bar");
    printf("\"foo\" + \"bar\" = \"%s\" (expected \"foobar\")\n", s5);

    return 0;
}

/* strcat_: concatenate t to end of s; s must be big enough */
void strcat_(char *s, char *t) {
        while (*s != '\0')
            s++;
        while ((*s++ = *t++))
            ;
        return;
}

