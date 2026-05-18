#include <stdio.h>

#define LINEPERPAGE 60
#define MAXLINE 1000

int main(int argc, char **argv) {
        char *prog = *argv;
        char line[MAXLINE];
        int page;
        int lcount;

        while (--argc > 0 && *++argv) {
                FILE *fp;
                if ((fp = fopen(*argv, "r")) == NULL)
                        fprintf(stderr, "%s: could not read %s\n", prog, *argv);
                else {
                        page = 1;
                        printf("\f%-72.72spage %3d\n", *argv, page++);
                        lcount = 1;
                        while (fgets(line, MAXLINE, fp)) {
                                if (lcount >= LINEPERPAGE) {
                                        printf("\f%-72.72spage %3d\n", *argv, page++);
                                        lcount = 1;
                                }
                                printf("%s", line);
                                lcount++;
                        }
                        if (ferror(fp))
                                fprintf(stderr, "%s: error reading %s\n", prog, *argv);
                        fclose(fp);
                }
        }
        return 0;
}
