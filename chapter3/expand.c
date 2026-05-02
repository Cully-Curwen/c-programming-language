#include <stdio.h>

#define MAXLINE 1000

void expand(char s1[], char s2[]);

int main(void) {
        char s[MAXLINE];

        expand("a-z", s);
        printf("\"a-z\" = \"%s\"\n", s);

        expand("A-Z", s);
        printf("\"A-Z\" = \"%s\"\n", s);

        expand("0-9", s);
        printf("\"0-9\" = \"%s\"\n", s);

        expand("a-f", s);
        printf("\"a-f\" = \"%s\"\n", s);

        expand("a-b-c", s);
        printf("\"a-b-c\" = \"%s\"\n", s);

        expand("a-z0-9", s);
        printf("\"a-z0-9\" = \"%s\"\n", s);

        expand("-a-z", s);
        printf("\"-a-z\" = \"%s\"\n", s);

        expand("a-z-", s);
        printf("\"a-z-\" = \"%s\"\n", s);

        expand("hello", s);
        printf("\"hello\" = \"%s\"\n", s);

        expand("a-cX-Zhello3-7", s);
        printf("\"a-cX-Zhello3-7\" = \"%s\"\n", s);

        return 0;
}

void expand(char s1[], char s2[]) {
        int i, j, c;

        for(i = j = 0; (s1[i]) != '\0'; i++) {
                if (s1[i] == '-' && (i != 0 && s1[i+1] != '\0'))
                        for (c = s1[i-1] + 1; c < s1[i+1]; c++)
                                s2[j++] = c;
                else
                        s2[j++] = s1[i];
        }
        s2[j] = '\0';
        return;
}
