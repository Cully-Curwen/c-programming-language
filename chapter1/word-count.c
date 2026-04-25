# include <stdio.h>

#define IN 1    /* inside a word */
#define OUT 0   /* outside a word */

/* count lines, words, and characters in input */
int main(void)
{
        int c, nl, nw, nc, state;

        state = OUT;
        nl = nw = nc = 0;
        while ((c = getchar()) != EOF) {
                ++nc;
                if (c == '\n')
                        ++nl;
                if (c == ' ' || c == '\n' || c == '\t')
                        state = OUT;
                else if (state == OUT) {
                        state = IN;
                        ++nw;
                }
        }
        printf("\nlines: %d  words: %d  characters:%d\n", nl, nw, nc);
}

/* Interesting bug, if you pass a text that does not end with a new line '\n' it does not count that line.
 * ie one line of text with no '\n' is treated as having 0 lines
 * So statring at 1 for lines would make some sense, but then passing an emptly string of "" will then say there is 1 line of text
 */

