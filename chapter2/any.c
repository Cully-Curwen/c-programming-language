#include <stdio.h>

int any(char s[], char c[]);

int main(void) {
        printf("any(\"hello world\", \"ol\") = %d\n", any("hello world", "ol"));
        printf("any(\"hello world\", \"xyz\") = %d\n", any("hello world", "xyz"));
        printf("any(\"abcdefg\", \"gf\") = %d\n", any("abcdefg", "gf"));
        printf("any(\"abcdefg\", \"fed\") = %d\n", any("abcdefg", "fed"));
        printf("any(\"programming\", \"aeiou\") = %d\n", any("programming", "aeiou"));
        printf("any(\"\", \"abc\") = %d\n", any("", "abc"));
        return 0;
}

int any(char s[], char c[]) {
        int i, j;

        for (i = 0; s[i] != '\0'; i++)
                for (j = 0; c[j] != '\0'; j++)
                        if (s[i] == c[j])
                                return i;
        return -1;
}
