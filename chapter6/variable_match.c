#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORD 100
#define N_DEFAULT 6

int getword(char *, int);
struct group *addgroup(struct group *, char *);
void treeprint(struct group *);

struct group {
        char *prefix;   /* first n characters */
        struct namelist *names; /* inner tree of full names */
        struct group *left;
        struct group *right;
};
struct namelist {
        char *name;
        struct namelist *left;
        struct namelist *right;
};
unsigned n = N_DEFAULT;

/* find variable names
 * ingnore strings and comments
 * us tree to store matches up to n characters
 * less or more in tree
 * Have an tree of trees for each new match group
 */
int main(int argc, char **argv) {
        struct group *root;
        char name[MAXWORD];

        if (--argc > 0 && isdigit(**++argv))
                n = (unsigned) atoi(*argv);

        root = NULL;

        while (getword(name, MAXWORD) != EOF) {
                if (isalpha(name[0]) || name[0] == '_')
                        root = addgroup(root, name);
        }
        treeprint(root);
        return 0;
}

struct group *talloc(void);
struct namelist *nalloc(void);
struct namelist *addname(struct namelist *, char *);
char *strsave(char *);

struct group *addgroup(struct group *p, char *name) {
        int cond;
        char prefix[n+1];

        if (p == NULL) {        /* a new name found */
                p = talloc();   /* make new group */
                strncpy(prefix, name, n);
                prefix[n] = '\0';
                p->prefix = strsave(prefix);
                p->names = addname(NULL, name);
                p->left = p->right = NULL;
        } else if ((cond = strncmp(name, p->prefix, n)) == 0)
                p->names = addname(p->names, name);
        else if (cond < 0)
                p->left = addgroup(p->left, name);
        else
                p->right = addgroup(p->right, name);
        return p;
}

struct namelist *addname(struct namelist *p, char *name) {
        int cond;

        if (p == NULL) {
                p = nalloc();
                p-> name = strsave(name);
                p->left = p->right = NULL;
        } else if ((cond = strcmp(name, p->name)) == 0)
                ;
        else if (cond < 0)
                p->left = addname(p->left, name);
        else
                p->right = addname(p->right, name);
        return p;
}

char *strsave(char *s) {
        char *p;

        p = (char *) malloc(strlen(s)+1);       /* +1 for '\0' */
        if (p != NULL)
                strcpy(p, s);
        return p;
}

struct group *talloc(void) {
        return (struct group *) malloc(sizeof(struct group));
}

struct namelist *nalloc(void) {
        return (struct namelist *) malloc(sizeof(struct namelist));
}

void nameprint(struct namelist *);
void treeprint(struct group *p) {
        if (p != NULL) {
                treeprint(p->left);
                printf("\n%s:\n\t", p->prefix);
                nameprint(p->names);
                treeprint(p->right);
        }
}

void nameprint(struct namelist *p) {
        if (p!= NULL) {
                nameprint(p->left);
                printf("%s, ", p->name);
                nameprint(p->right);
        }
}

/* getword: get next word or character from input */
int getword(char *word, int lim) {
        int c, getch(void);
        void ungetch(int);
        char *w = word;

        while (isspace(c = getch()))
                ;
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
