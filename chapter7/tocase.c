#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(int _, char **argv) {
        int c;

        while ((c = getchar()) != EOF) {
                if (strstr(*argv, "lower"))
                        c = tolower(c);
                else
                        c = toupper(c);

                printf("%c", c);
        }

        return 0;
}
