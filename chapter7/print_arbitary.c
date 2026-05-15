#include <ctype.h>
#include <stdio.h>

#define MAXBUFFER       10
#define MAXCOLUMN       80

/* print arbitary input
 * collect input into line strings
 * convert non isprint() to hex
 * when length > MAXCOLUMN fold line
 * print
 */
int main(void) {
        int c, col = 0;
        char buff[MAXBUFFER];

        while ((c = getchar()) != EOF) {
                 if (c == '\n') {
                         sprintf(buff, "%c", c);
                         col = 0;
                 } else if (isprint(c)) {
                         sprintf(buff, "%c", c);
                         col++;
                 } else {
                         sprintf(buff, "0x%02x", c);
                         col += 4;
                 }

                 if (col > MAXCOLUMN) {
                         printf("\n");
                         col = 0;
                 }
                 printf("%s", buff);
        }

        return 0;
}
