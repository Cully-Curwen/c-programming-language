#include <stdio.h>

#define MAXLENGTH 30 /* max length of word recorded, max 99 */

/* Create a histogram of the length of words */

int main(void) {
        int c, wlength;
        int lengths[MAXLENGTH] = {0};

        wlength = 0;
        while ((c = getchar()) != EOF) {
                if (c == ' ' || c == '\t' || c == '\n') {
                        if (wlength > 0 && wlength <= MAXLENGTH) {
                                lengths[wlength - 1]++;
                        }
                        else if (wlength > MAXLENGTH) {
                                lengths[MAXLENGTH -1]++;
                        }
                        wlength = 0;
                }
                else {
                        wlength++;
                }
        }

        for (int i = 0; i < MAXLENGTH; i++) {
                if (i == MAXLENGTH - 1)
                        printf("\n%2d+:", MAXLENGTH);
                else
                        printf("\n%3d:", i + 1);
                for (int n = 0; n < lengths[i]; n++) {
                        printf("*");
                }
        }
}

