#include <stdio.h>

#define MAXLINE 1000

int strrindex(char s[], char t []);

int main(void) {
        printf("strrindex(\"hello world\", \"lo\") = %d (expect 3)\n",
                strrindex("hello world", "lo"));

        printf("strrindex(\"abcabcabc\", \"abc\") = %d (expect 6)\n",
                strrindex("abcabcabc", "abc"));

        printf("strrindex(\"abcabcabc\", \"xyz\") = %d (expect -1)\n",
                strrindex("abcabcabc", "xyz"));

        printf("strrindex(\"hello\", \"hello\") = %d (expect 0)\n",
                strrindex("hello", "hello"));

        printf("strrindex(\"aaa\", \"a\") = %d (expect 2)\n",
                strrindex("aaa", "a"));

        printf("strrindex(\"\", \"abc\") = %d (expect -1)\n",
                strrindex("", "abc"));

        printf("strrindex(\"hello world\", \"orld\") = %d (expect 7)\n",
                strrindex("hello world", "orld"));

        printf("strrindex(\"the cat sat on the mat\", \"the\") = %d (expect 15)\n",
                strrindex("the cat sat on the mat", "the"));

        return 0;
}

/* strrindex: return the right most index of t in s, -1 if none */
int strrindex(char s[], char t []) {
        int i, j, k, match;

        match = -1;
        for (i = 0; s[i] != '\0'; i++) {
                for (j=i, k=0; t[k]!='\0' && s[j]==t[k]; j++, k++)
                        ;
                if (k > 0 && t[k] == '\0')
                        match = i;
        }
        return match;
}
