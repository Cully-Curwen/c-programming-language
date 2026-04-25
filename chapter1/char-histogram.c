#include <stdio.h>

#define CHARS 128 /* Using 128 as this is the number of ASCII Characters */

/* Count each instant of an ASCII Character and create a histogram, excluding control characters */
int main(void) {
        int c;
        int nChar[CHARS] = {0};

        while ((c = getchar()) != EOF) {
                nChar[c]++;
        }

        for (int i = 33; i < 127; i++) {
                printf("\n%3c:", i);
                for (int n = 0; n < nChar[i]; n++) {
                        printf("*");
                }
        }
}
