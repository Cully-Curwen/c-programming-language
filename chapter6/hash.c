/* K&R 2nd Edition, Section 6.6 - Table Lookup
 *
 * A hash table implementation used to store name/definition pairs,
 * as you'd find in a C preprocessor (#define substitutions).
 *
 * The table is an array of linked lists (HASHSIZE buckets).
 * Each entry holds: a name, a definition, and a next pointer.
 *
 * Compile: cc kr_6_6_hashtable.c -o hashtable
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 101   /* number of hash buckets; prime helps spread entries */

/* --- Data Structure ---------------------------------------------------- */

struct nlist {          /* table entry */
    struct nlist *next; /* next entry in chain (for collision handling) */
    char *name;         /* defined name */
    char *defn;         /* replacement text */
};

/* The hash table itself: an array of pointers to nlist structs.
 * Each element is the head of a linked list for that bucket.
 * Initialised to all-NULLs by C's default for static storage. */
static struct nlist *hashtab[HASHSIZE];

/* --- hash: form hash value for string s -------------------------------- */
/* Walks every character, accumulating into an unsigned int, then
 * takes the remainder mod HASHSIZE to get a bucket index [0..100]. */
unsigned int hash(char *s)
{
    unsigned int hashval;

    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}

/* --- lookup: look for s in hashtab ------------------------------------- */
/* Returns a pointer to the matching nlist entry, or NULL if not found.
 * Starts at the head of the bucket's linked list and walks the chain
 * comparing names with strcmp. */
struct nlist *lookup(char *s)
{
    struct nlist *np;

    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np;   /* found */
    return NULL;         /* not found */
}

/* --- mystrdup: make a private copy of a string ------------------------- */
/* (Named to avoid clashing with standard library strdup.) */
static char *mystrdup(char *s)
{
    char *p = (char *) malloc(strlen(s) + 1);
    if (p != NULL)
        strcpy(p, s);
    return p;
}

/* --- install: put (name, defn) in hashtab ------------------------------ */
/* Returns a pointer to the installed entry, or NULL on failure.
 * If the name already exists its definition is replaced.
 * If it is new, a fresh nlist is allocated and prepended to the bucket. */
struct nlist *install(char *name, char *defn)
{
    struct nlist *np;
    unsigned int hashval;

    if ((np = lookup(name)) == NULL) {   /* name not found: create new entry */
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->name = mystrdup(name)) == NULL)
            return NULL;                 /* out of memory */
        hashval = hash(name);
        np->next = hashtab[hashval];     /* prepend to bucket's list */
        hashtab[hashval] = np;
    } else                               /* name already there: free old defn */
        free((void *) np->defn);

    if ((np->defn = mystrdup(defn)) == NULL)
        return NULL;                     /* out of memory */
    return np;
}

void undef(char *s) {
        unsigned hashval = hash(s);
        struct nlist *prevp, *np, *nextp;

        prevp = NULL;
        for (np = hashtab[hashval]; np != NULL; np = np->next) {
            if (strcmp(s, np->name) == 0) {
                break;
            }
            prevp = np;
        }
        nextp = np->next;   /* either a nlist or NULL */
        free(np->name);
        free(np->defn);
        free((void *) np);
        if (prevp)
            prevp->next = nextp;
        else
            hashtab[hashval] = nextp;
        return;
}

// int main(void)
// {
//     struct nlist *p;
//
//     /* Install some definitions (like #define in C) */
//     install("IN",   "1");
//     install("OUT",  "0");
//     install("YES",  "1");
//     install("NO",   "0");
//     install("MAX",  "100");
//
//     /* Look one up and print it */
//     if ((p = lookup("MAX")) != NULL)
//         printf("MAX  -> %s\n", p->defn);
//     else
//         printf("MAX not found\n");
//
//     /* Re-define an existing entry */
//     install("MAX", "9999");
//     if ((p = lookup("MAX")) != NULL)
//         printf("MAX (redefined) -> %s\n", p->defn);
//
//     undef("MAX");
//     if ((p = lookup("MAX")) != NULL)
//             printf("MAX -> %s\n", p->defn);
//     else
//             printf("MAX not found\n");
//
//     /* Try a name that was never installed */
//     if (lookup("MISSING") == NULL)
//         printf("MISSING -> (not found)\n");
//
//     return 0;
// }
