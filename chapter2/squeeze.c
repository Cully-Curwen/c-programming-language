#include <stdio.h>

void squeeze(char s[], char c[]);

int main(void) {
        char s1[] = "hello world";
        char s2[] = "goodbye cruel world";
        char s3[] = "abcdefghijk";
        char s4[] = "the quick brown fox jumps over the lazy dog";
        char s5[] = "aeiou";
        char s6[] = "programming";

        printf("before: \"%s\"\n", s1);
        squeeze(s1, "lo");
        printf("after squeeze with \"lo\": \"%s\"\n\n", s1);

        printf("before: \"%s\"\n", s2);
        squeeze(s2, "aeiou");
        printf("after squeeze with \"aeiou\": \"%s\"\n\n", s2);

        printf("before: \"%s\"\n", s3);
        squeeze(s3, "bdf");
        printf("after squeeze with \"bdf\": \"%s\"\n\n", s3);

        printf("before: \"%s\"\n", s4);
        squeeze(s4, "the");
        printf("after squeeze with \"the\": \"%s\"\n\n", s4);

        printf("before: \"%s\"\n", s5);
        squeeze(s5, "xyz");
        printf("after squeeze with \"xyz\": \"%s\"\n\n", s5);

        printf("before: \"%s\"\n", s6);
        squeeze(s6, "grim");
        printf("after squeeze with \"grim\": \"%s\"\n\n", s6);

        return 0;
}

void squeeze(char s[], char c[]) {
        int i, j, k;

        for (k = 0; c[k] != '\0'; k++) {
                for (i = j = 0; s[i] != '\0'; i++)
                        if (s[i] != c[k])
                                s[j++] = s[i];
                s[j] = '\0';
        }
}
