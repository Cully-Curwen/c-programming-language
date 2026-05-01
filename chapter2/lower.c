#include <stdio.h>

int lower(int c);

int main(void) {
        printf("lower('A') = '%c' (expect 'a')\n", lower('A'));
        printf("lower('Z') = '%c' (expect 'z')\n", lower('Z'));
        printf("lower('M') = '%c' (expect 'm')\n", lower('M'));
        printf("lower('a') = '%c' (expect 'a')\n", lower('a'));
        printf("lower('z') = '%c' (expect 'z')\n", lower('z'));
        printf("lower('5') = '%c' (expect '5')\n", lower('5'));
        printf("lower(' ') = '%c' (expect ' ')\n", lower(' '));
        printf("lower('!') = '%c' (expect '!')\n", lower('!'));
        return 0;
}

int lower(int c) {
        // if (c >= 'A' && c <= 'Z')
        //         return c + 'a' - 'A';
        // else return c;

        return (c >= 'A' && c <= 'Z') ? (c + 'a' - 'A') : c;
}
