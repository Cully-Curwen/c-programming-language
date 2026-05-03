#include <stdio.h>
#include <stdlib.h>    /* for atof() */
#include <string.h>
#include <math.h>
#include <ctype.h>

#define MAXOP   100     /* max size of operand or operator */
#define NUMBER  '0'     /* signal that a number was found */
#define NAME    'n'     /* signal that a named function was found */
#define VARIABLE 'v'    /* signal that a variable has been found */

int getop(char []);
void push(double);
double pop(void);

/* reverse Polish calculator */
int main(void) {
        int type;
        double op2;
        char s[MAXOP];
        int v;
        double vars[26];
        double last;

        while ((type = getop(s)) != EOF) {
                switch (type) {
                case NUMBER:
                        push(atof(s));
                        break;
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
                case NAME:
                        if (strcmp(s, "sin") == 0)
                                push(sin(pop()));
                        else if (strcmp(s, "exp") == 0)
                                push(exp(pop()));
                        else if (strcmp(s, "pow") == 0) {
                                op2 = pop();
                                push(pow(pop(), op2));
                        }
                        else
                                printf("error: unknown function %s\n", s);
                        break;
                case VARIABLE:
                        v = toupper(s[0]) - 'A';
                        push(vars[v]);
                        break;
                case '=':
                        op2 = pop();
                        vars[v] = (vars[v] == op2) ? pop() : op2;
                        printf("%c <= ", v + 'A');
                        push(vars[v]);
                        break;
                case '_':
                        push(last);
                        break;
                case '\n':
                        last = pop();
                        printf("\t%.8g\n", last);
                        break;
                default:
                        printf("error: unknown command %s\n", s);
                        break;
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

/* getop: get next operator or numeric operand */
#include <ctype.h>

int getch(void);
void ungetch(int);

int getop(char s[]) {
        int i, c;

        while ((s[0] = c = getch()) == ' ' || c == '\t')
                ;
        s[1] = '\0';
        if (!isdigit(c) && c != '.' && c != '-' && !isalpha(c)) {
                return c;       /* not a number or - */
        }
        i = 0;
        if (c == '-') {
                if (!isdigit(c = getch()) && c != '.') {
                        ungetch(c);
                        return '-';
                } else {
                        s[++i] = c;
                }
        }
        if (isalpha(c)) {        /* collect letter part */
                while (isalpha(s[++i] = c = getch()))
                        ;
                s[i] = '\0';
                if (c != EOF)
                        ungetch(c);
                return (i == 1) ? VARIABLE : NAME;
        }
        if (isdigit(c))         /* collect integer part */
                while (isdigit(s[++i] = c = getch()))
                        ;
        if (c == '.')           /* collect fraction part */
                while (isdigit(s[++i] = c = getch()))
                        ;
        s[i] = '\0';
        if (c != EOF)
                ungetch(c);
        return NUMBER;
}

/* getch and ungetch */
/* ex 4-8 if there is only ever 1 character of push back there is no need for a buf[]
 * can be held in a variable char buf;
 * bufp and BUFSIZE would then not be needed, aswell as less memory being allocated
 */
#define BUFSIZE 100

/* EOF is -1 so depending on machine char migtht not store -1 correctly
 * by using int it cannot be corvesion on storing
 */
int buf[BUFSIZE];      /* buffer for ungetch */
int bufp = 0;           /* next free position in buf */

/* getch: get a (possibly pushed back) character */
int getch(void) {
        return (bufp > 0) ? buf[--bufp] : getchar();
}

/* ungetch: push character back on input */
void ungetch(int c) {
        if (bufp >= BUFSIZE)
                printf("ungetch: too many characters\n");
        else
                buf[bufp++] = c;
        return;
}

/* ungets: push string back onto input */
void ungets(char s[]) {
        int i, len;

        len = strlen(s);
        if (bufp >= BUFSIZE - len)
                printf("ungets: string to large\n");
        else
                for (i = len - 1; i >= 0; i--)
                        ungetch(s[i]);
        return;
}

/* print: print the top element of the stack, without poping */
void print(void) {
        if (sp > 0)
                printf("%g\n", val[sp-1]);
        else {
                printf("error: stack empty\n");
        }
        return;
}

/* duplicate: duplicate the top element of the stack */
void duplicate(void) {
        if (sp > 0 && sp < MAXVAL) {
                val[sp] = val[sp-1];
                sp++;
        } else if (sp == 0) {
                printf("error: stack empty, can't duplicate\n");
        } else {
                printf("error: stack full, can't duplicate\n");
        }
        return;
}

/* swap: swaps the top two element of the stack */
void swap(void) {
        double val1, val2;

        if (sp >= 2) {
                val1 = pop();
                val2 = pop();
                push(val1);
                push(val2);
        } else {
                printf("error: less than 2 element in stack, can't swap\n");
        }
        return;
}

/* clear: clear the stack */
void clear(void) {
        sp = 0;
        return;
}

