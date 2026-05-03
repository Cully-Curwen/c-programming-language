#include <stdio.h>
#include <string.h>

void reverse(char s[]);

int main(void) {
        char s1[] = "hello";
        reverse(s1);
        printf("reverse(\"hello\") = \"%s\" (expect \"olleh\")\n", s1);

        char s2[] = "abcdef";
        reverse(s2);
        printf("reverse(\"abcdef\") = \"%s\" (expect \"fedcba\")\n", s2);

        char s3[] = "a";
        reverse(s3);
        printf("reverse(\"a\") = \"%s\" (expect \"a\")\n", s3);

        char s4[] = "";
        reverse(s4);
        printf("reverse(\"\") = \"%s\" (expect \"\")\n", s4);

        char s5[] = "ab";
        reverse(s5);
        printf("reverse(\"ab\") = \"%s\" (expect \"ba\")\n", s5);

        char s6[] = "racecar";
        reverse(s6);
        printf("reverse(\"racecar\") = \"%s\" (expect \"racecar\")\n", s6);

        return 0;
}


int i;

void reverse(char s[]) {
        int c1, c2;
        int len = strlen(s);

        if (i >= len - i) {
                i = 0;
                return;
        }

        c1 = s[i];
        c2 = s[len-i-1];

        s[i] = c2;
        s[len-i-1] = c1;
        i++;

        reverse(s);
}
