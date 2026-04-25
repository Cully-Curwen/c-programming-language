#include <stdio.h>

#define IN  1 /* inside a word */
#define OUT 0 /* outside a word */

int main(void) {
        int c, state;

        state = OUT;
        while ((c = getchar()) != EOF) {
                if (c == ' ' || c == '\t' || c == '\n') {
                        state = OUT;
                        printf("\n");
                }
                else if (state == OUT) {
                        state = IN;
                }
                if (state == IN)
                        printf("%c", c);
        }
}
