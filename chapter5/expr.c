#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXOPS 100
#define NUMBER '0'

int main(int argc, char *argv[]) {
        /* get each argument 
         * check if operator or number ( number could be negative )
         * if number add to stack, if operator get from stack and do operation
         * push result onto stack
         * when no operator left print pop from stack
         * if invalid argument print error
         */
        double op[MAXOPS];
        double *ops = op, *opsb = ops;
        while (argc-- > 1) {
                ++argv;
                if (isdigit(**argv) || ((**argv == '-' || **argv == '+') && isdigit(*(*argv+1)))) {
                        *ops++ = atof(*argv);
                        **argv = NUMBER;
                }

                switch (**argv) {
                        double temp;
                        case NUMBER:
                                break;
                        case '-':
                                if (ops - opsb > 1) {
                                        temp = *--ops;
                                        *(ops-1) -= temp;
                                } else if (ops - opsb == 1) {
                                        *(ops-1) = -*(ops-1);
                                } else {
                                        printf("error: empty\n");
                                }
                                break;
                        case '+':
                                if (ops - opsb > 1) {
                                        temp = *--ops;
                                        *(ops-1) += temp;
                                } else if (ops - opsb == 1) {
                                        break;
                                } else {
                                        printf("error: empty\n");
                                }
                                break;
                        case '*':
                                if (ops - opsb > 1) {
                                        temp = *--ops;
                                        *(ops-1) *= temp;
                                } else if (ops - opsb == 1) {
                                        printf("error: to few args\n");
                                } else {
                                        printf("error: empty\n");
                                }
                                break;
                        case '/':
                                if (ops - opsb > 1) {
                                        temp = *--ops;
                                        *(ops-1) /= temp;
                                } else if (ops - opsb == 1) {
                                        printf("error: to few args\n");
                                } else {
                                        printf("error: empty\n");
                                }
                                break;
                        default:
                                printf("error: operator not recognised\n");
                                return -1;
                                break;
                }
        }

        if (ops - opsb == 1)
                printf("\t%g", *--ops);
        else
                printf("pass valid numbers and operations\n");
        return 0;
}
