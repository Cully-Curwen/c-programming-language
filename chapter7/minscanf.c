#include <stdarg.h>
#include <stdio.h>

/* minscanf: minimal printf with variable argument list */
void minscanf(char *fmt, ...) {
        va_list ap;    /* points to each unnamed arg in turn */
        char *p, *sp, *cp, c;
        int *ip;
        float *fp;
        unsigned *up;

        va_start(ap, fmt);      /* make ap point to 1st unnamed arg */
        for (p = fmt; *p; p++) {
                if (*p != '%') {
                        if ((c = getchar()) == *++p)
                                continue;
                        else
                                break;
                }
                switch (*++p) {
                case 'd':
                case 'i':
                        ip = va_arg(ap, int *);
                        scanf("%d", ip);
                        break;
                case 'c':
                        cp = va_arg(ap, char *);
                        scanf("%c", cp);
                        break;
                case 'o':
                        up = va_arg(ap, unsigned *);
                        scanf("%o", up);
                        break;
                case 'x':
                        up = va_arg(ap, unsigned *);
                        scanf("%x", up);
                        break;
                case 'u':
                        up = va_arg(ap, unsigned *);
                        scanf("%u", up);
                        break;
                case 'f':
                        fp = va_arg(ap, float *);
                        scanf("%f", fp);
                        break;
                case 'e':
                        fp = va_arg(ap, float *);
                        scanf("%e", fp);
                        break;
                case 'g':
                        fp = va_arg(ap, float *);
                        scanf("%g", fp);
                        break;
                case 's':
                        sp = va_arg(ap, char *);
                        scanf("%s", sp);
                        break;
                case '%':
                        scanf("%%");
                        break;
                default:
                        break;
                }
        }
        va_end(ap);     /* clean up when done */
}

