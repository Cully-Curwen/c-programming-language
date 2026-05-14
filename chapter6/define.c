#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "hash.h"

#define MAXWORD         100

/* get line
 * if line[0] #
 * if getword define -> define logic
 * -> getword for name
 * -> getword for def
 * -> install in hashtable
 * if getword undefine -> undefine logic
 * get name then undef(name)
 * else print line
 *
 * else
 * read/print logic
 */
int main(void) {
        int c;

        while ((c = getch()) != EOF) {
                if (c == '"') {
                        printf("\"");
                        while ((c = getch()) != EOF) {
                                if (c == '\\') {
                                        c = getch();
                                        printf("\\%c", c);
                                } else if (c == '"') {
                                        printf("\"");
                                        break;
                                } else {
                                        printf("%c", c);
                                }
                        }
                } else if (c == '/') {
                        printf("/");
                        if ((c = getch()) == '*') {
                                printf("*");
                                while ((c = getch()) != EOF) {
                                        if (c == '*') {
                                                printf("*");
                                                if ((c = getch()) == '/') {
                                                        printf("/");
                                                        break;
                                                } else {
                                                        ungetch(c);
                                                }
                                        } else {
                                                printf("%c", c);
                                        }
                                }
                        } else {
                                ungetch(c);
                        }
                } else if (c == '#') {
                        char directive[MAXWORD];
                        getword(directive, MAXWORD);
                        if (strcmp(directive, "define") == 0) {
                                char name[MAXWORD];
                                char def[MAXWORD];
                                getword(name, MAXWORD);
                                getword(def, MAXWORD);
                                install(name, def);
                                while ((c = getch()) != '\n')
                                        ;
                                printf("\n");
                        } else if (strcmp(directive, "undef") == 0) {
                                char name[MAXWORD];
                                getword(name, MAXWORD);
                                undef(name);
                                while ((c = getch()) != '\n')
                                        ;
                                printf("\n");
                        } else {
                                printf("#%s", directive);
                                while ((c = getch()) != '\n')
                                        printf("%c", c);
                                printf("\n");
                        }
                } else if (isalpha(c) || c == '_') {
                        char word[MAXWORD];
                        struct nlist *np;
                        ungetch(c);
                        getword(word, MAXWORD);
                        np = lookup(word);
                        if (np)
                                printf("%s", np->defn);
                        else
                                printf("%s", word);
                } else {
                        printf("%c", c);
                }
        }
}


