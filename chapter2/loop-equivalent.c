#include <stdio.h>

#define MAXLINE 1000

int main(void) {
        int i;
        int lim = MAXLINE;
        char c;

        // for (i=0; i<lim-1 && (c=getchar()) != '\n' && c != EOF; ++i);

        for (i=0; i < lim - 1; ++i) {
                if ((c = getchar()) == '\n')
                        break;
                if (c == EOF)
                        break;
                // does something
        }

        i = 0;
        while (i < lim - 1) {
                if ((c = getchar()) != '\n')
                        if (c == EOF) {
                                // does something
                                ++i;
                        }
        }

        return 0;
}
