/* hash.h - hash table interface (K&R 6.6) */

#ifndef HASH_H
#define HASH_H

struct nlist {
        struct nlist *next;
        char *name;
        char *defn;
};

unsigned int    hash(char *s);
struct nlist   *lookup(char *s);
struct nlist   *install(char *name, char *defn);
void            undef(char *s);


int             getword(char *word, int lim);
int getch(void);
void ungetch(int c);

#endif
