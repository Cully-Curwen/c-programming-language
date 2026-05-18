#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

/* get 2 file pointer
 * open both for read
 * get line for each file
 * str compare both lines
 * if not same print both lines
 */
int main(int argc, char **argv) {
        FILE *fp1, *fp2;
        char *name1, *name2;
        char line1[MAXLINE], line2[MAXLINE];
        int i;

        if (argc < 3) {
                printf("error: need two file name arguments");
                return -1;
        }
        name1 = argv[1];
        name2 = argv[2];
        if ((fp1 = fopen(name1, "r")) == NULL) {
                printf("error: cannot open %s\n", name1);
                return -1;
        }
        if ((fp2 = fopen(name2, "r")) == NULL) {
                printf("error: cannot open %s\n", name2);
                return -1;
        }
        i = 0;
        while (fgets(line1, MAXLINE, fp1) && fgets(line2, MAXLINE, fp2)) {
                i++;
                if (strcmp(line1, line2)) {
                        printf("Line differ on line: %d\n%s:\n%s\n%s:\n%s", i, name1, line1, name2, line2);
                        return 0;
                }
        }

        if (ferror(fp1) || ferror(fp2)) {
                if (ferror(fp1))
                        printf("error: reading %s\n", name1);
                if (ferror(fp2))
                        printf("error: reading %s\n", name2);
                fclose(fp1);
                fclose(fp2);
                return -1;
        }

        printf("files match\n");

        fclose(fp1);
        fclose(fp2);
        return 0;
}
