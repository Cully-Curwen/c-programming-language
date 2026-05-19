#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#define BUFSIZE 1000 /* use BUFSIZ from stdio.h, is x3 performance */

void error(char *, ...);

/* cat: concatenate files */
int main(int argc, char **argv) {
        int f, n;
        char buf[BUFSIZ];
        char *prog = *argv;

        if (argc == 1) {
                while ((n = read(0, buf, BUFSIZ)) > 0)
                        write(1, buf, n);
        } else {
                while (--argc > 0 && ++argv) {
                        if ((f = open(*argv, O_RDONLY, 0)) == -1)
                                error("%s: can't open %s", prog, *argv);
                        while ((n = read(f, buf, BUFSIZ)) > 0)
                                if (write(1, buf, n) != n)
                                        error("%s: write error on file %s", prog, *argv);
                        close(f);
                }
        }
        return 0;
}

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void error(char *fmt, ...) {
        va_list args;

        va_start(args, fmt);
        fprintf(stderr, "error: ");
        vfprintf(stderr, fmt, args);
        fprintf(stderr, "\n");
        va_end(args);
        exit(1);
}
