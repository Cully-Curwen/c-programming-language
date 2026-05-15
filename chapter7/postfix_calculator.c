#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define MAXOP   100     /* max size of operand or operator */

void push(double);
double pop(void);

/* reverse Polish calculator */
int main(void) {
        double op, op2;
        char s[MAXOP];
        int v;
        double vars[26];
        double last;

        while ((scanf("%s", s)) != EOF) {
                if (sscanf(s, "%lf", &op)) {
                        push (op);
                } else {
                        switch (*s) {
                        case '+':
                                push(pop() + pop());
                                break;
                        case '*':
                                push(pop() * pop());
                                break;
                        case '-':
                                op2 = pop();
                                push(pop() - op2);
                                break;
                        case '/':
                                op2 = pop();
                                if (op2 != 0.0)
                                        push(pop() / op2);
                                else
                                        printf("error: zero divisor\n");
                                break;
                        case '%':
                                op2 =  pop();
                                if (op2 != 0.0)
                                        push((int)pop() % (int)op2);
                                else
                                        printf("error: zero divisor\n");
                                break;
                        case ':':
                                op2 = pop();
                                vars[v] = (vars[v] == op2) ? pop() : op2;
                                printf("%c <= ", v + 'A');
                                push(vars[v]);
                                break;
                        case '_':
                                push(last);
                                break;
                        case '=':
                                last = pop();
                                printf("\t%.8g\n", last);
                                break;
                        default:
                                if (strlen(s) == 1 && isalpha(s[0])) {  /* VARIALE */
                                        v = toupper(s[0]) - 'A';
                                        push(vars[v]);
                                } else if (strcmp(s, "sin") == 0) {
                                        push(sin(pop()));
                                } else if (strcmp(s, "exp") == 0) {
                                        push(exp(pop()));
                                } else if (strcmp(s, "pow") == 0) {
                                        op2 = pop();
                                        push(pow(pop(), op2));
                                } else {
                                        printf("error: unknown command %s\n", s);
                                }
                                break;
                        }
                }
        }
        return 0;
}

/* stack */
#define MAXVAL  100    /* maximum depth of val stack */

int sp = 0;             /* next free stack position */
double val[MAXVAL];     /* value stack */

/* push: push f onto value stack */
void push(double f) {
        if (sp < MAXVAL)
                val[sp++] = f;
        else
                printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void) {
        if (sp > 0)
                return val[--sp];
        else {
                printf("error: stack empty\n");
                return 0.0;
        }
}
