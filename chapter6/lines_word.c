#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORD 100
#define MAXLINES 1000
#define N_DEFAULT 6

int getword(char *, int);
struct tnode *addtnode(struct tnode *, char *, int);
void treeprint(struct tnode *);

struct tnode {
        char *word;
        int *line;
        struct tnode *left;
        struct tnode *right;
};

/* get word
 * remove noise 'and', 'the'
 * track line number
 * create tree of words, with arry of line ints
 */
int main(void) {
        struct tnode *root;
        char word[MAXWORD];
        int line;

        root = NULL;
        line = 1;

        while (getword(word, MAXWORD) != EOF) {
                if (word[0] == '\n')
                        line++;
                if (isalpha(word[0]) || word[0] == '_')
                        root = addtnode(root, word, line);
        }
        treeprint(root);
        return 0;
}

struct tnode *talloc(void);
int *linealloc(void);
char *strsave(char *);
int *linesave(int *, int);

struct tnode *addtnode(struct tnode *p, char *word, int line) {
        int cond;
        int *lp;

        if (p == NULL) {        /* a new name found */
                p = talloc();   /* make new tnode */
                p->word = strsave(word);
                lp = linealloc();
                p->line = linesave(lp, line);
                p->left = p->right = NULL;
        } else if ((cond = strcmp(word, p->word)) == 0)
                p->line = linesave(p->line, line);
        else if (cond < 0)
                p->left = addtnode(p->left, word, line);
        else
                p->right = addtnode(p->right, word, line);
        return p;
}

char *strsave(char *s) {
        char *p;

        p = (char *) malloc(strlen(s)+1);       /* +1 for '\0' */
        if (p != NULL)
                strcpy(p, s);
        return p;
}

int *linesave(int *p, int n) {
        int *lp = p;
        for ( ; *lp && (lp - p) < MAXLINES-1; lp++)
          if (*lp == n)
                  return p;
        *lp = n;
        *++lp = '\0';
        return p;
}

struct tnode *talloc(void) {
        return (struct tnode *) malloc(sizeof(struct tnode));
}

int *linealloc(void) {
        int *p;

        p = (int *) malloc(MAXLINES * sizeof(int));
        if (p!= NULL)
                *p = '\0';
        return p;
}

void treeprint(struct tnode *p) {
        if (p != NULL) {
                treeprint(p->left);
                printf("\n%s:\n\t", p->word);
                int *lp = p->line;
                for ( ; *lp; lp++)
                        printf("%d, ", *lp);
                printf("\n");
                treeprint(p->right);
        }
}

/* getword: get next word or character from input */
int getword(char *word, int lim) {
        int c, getch(void);
        void ungetch(int);
        char *w = word;

        while (isspace(c = getch())) {
                if (c == '\n') {
                        *w++ = c;
                        break;
                }
        }
        if (c != EOF)
                *w++ = c;
        if (c == '\\')
                c = getch();
        if (c == '"') {
                while ((c = getch()) != EOF) {
                        if (c == '\\')
                                getch();
                        else if (c == '"')
                                break;
                }
        }
        if (c == '#')
                while ((c = getch()) != EOF)
                        if (c == '\n')
                                break;
        if (c == '/') {
                if ((c = getch()) == '*')
                       while ((c = getch()) != EOF) {
                               if (c == '*' && (c = getch()) == '/')
                                       break;
                       }
                else {
                        ungetch(c);
                        c = '/';
                }
        }
        if (!isalpha(c) && c != '_') {
                *w = '\0';
                return c;
        }
        for ( ; --lim > 0; w++)
                if (!isalnum(*w = getch()) && *w != '_') {
                        ungetch(*w);
                        break;

                }
        *w = '\0';
        return word[0];
}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
        return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
        if (bufp >= BUFSIZE)
                printf("ungetch: too many characters\n");
        else
                buf[bufp++] = c;
}
