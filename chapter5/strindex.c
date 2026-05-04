#include <stdio.h>

int strindex(char *, char *);

int main(void)
{
        printf("strindex(\"hello world\", \"world\") = %d (expected 6)\n", strindex("hello world", "world"));
        printf("strindex(\"hello world\", \"hello\") = %d (expected 0)\n", strindex("hello world", "hello"));
        printf("strindex(\"hello world\", \"xyz\") = %d (expected -1)\n", strindex("hello world", "xyz"));
        printf("strindex(\"abcabc\", \"abc\") = %d (expected 0)\n", strindex("abcabc", "abc"));
        printf("strindex(\"abcabc\", \"cab\") = %d (expected 2)\n", strindex("abcabc", "cab"));
        printf("strindex(\"\", \"abc\") = %d (expected -1)\n", strindex("", "abc"));
        printf("strindex(\"abc\", \"\") = %d (expected 0)\n", strindex("abc", ""));
        printf("strindex(\"abc\", \"abc\") = %d (expected 0)\n", strindex("abc", "abc"));

        return 0;
}

/* strindex: return the index when t is found in s, otherwise -1 */
// int strindex(char *s, char *t) {
//         int i, j;
//
//         for (i=0; *s; i++) {
//                 for (j=0; *t && *s == *t; j++) {
//                         s++;
//                         t++;
//                 }
//                 if (*t == '\0') {
//                         return i;
//                 } else {
//                         s -= j;
//                         t -= j;
//                 }
//                 s++;
//         }
//
//         return -1;
// }

/* strindex: return the index when t is found in s, otherwise -1 */
int strindex(char *s, char *t) {
        char *sb = s;

        while (*s) {
                char *sp = s;
                char *tp = t;

                while (*tp && *sp == *tp) {
                        sp++;
                        tp++;
                }

                if (*tp == '\0')
                        return s - sb;

                s++;
        }

        return -1;
}
