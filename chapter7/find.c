#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

int _getline(char *line, int max);

/* find: print lines that match pattern from 1st arg, argv++ are files */
int main(int argc, char **argv) {
        char line[MAXLINE];
        long lineno = 0;
        int c, except = 0, number = 0, found = 0;
        char *prog = *argv;

        while (--argc > 0 && (*++argv)[0] == '-') {
                while ((c = *++argv[0]))
                        switch (c) {
                        case 'x':
                                except = 1;
                                break;
                        case 'n':
                                number = 1;
                                break;
                        default:
                                printf("find: illegal option %c\n", c);
                                argc = 0;
                                found = -1;
                                break;
                        }
        }
        if (argc < 1)
                printf("Usage: %s [-x] [-n] pattern [files]\n", prog);
        else if ( argc == 1) {
                while (_getline(line, MAXLINE) > 0) {
                        lineno++;
                        if ((strstr(line, *argv) != NULL) != except) {
                                if (number)
                                        printf("%ld:", lineno);
                                printf("%s", line);
                                found++;
                        }
                }
        } else {
                char *pattern = *argv;
                int nfiles = argc - 1;
                while (--argc > 0 && *++argv) {
                        FILE *fp;
                        lineno = 0;
                        if ((fp = fopen(*argv, "r")) == NULL) {
                                fprintf(stderr, "%s: could not read %s", prog, *argv);
                        } else {
                                while (fgets(line, MAXLINE, fp)) {
                                        lineno++;
                                        if ((strstr(line, pattern) != NULL) != except) {
                                                if (nfiles > 1)
                                                        printf("%s:", *argv);
                                                if (number)
                                                        printf("%ld:", lineno);
                                                printf("%s", line);
                                                found++;
                                        }
                                }
                        fclose(fp);
                        }
                }
        }
        return found;
}

/* _getline: read a line, return length */
int _getline(char *line, int max) {
        if (fgets(line, max ,stdin) == NULL)
                return 0;
        else
                return strlen(line);
}
