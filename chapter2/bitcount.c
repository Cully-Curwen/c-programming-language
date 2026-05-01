#include <stdio.h>

int bitcount(unsigned x);

int main(void) {
        printf("bitcount(0) = %d (expect 0)\n", bitcount(0));
        printf("bitcount(1) = %d (expect 1)\n", bitcount(1));
        printf("bitcount(170) = %d (expect 4)\n", bitcount(170));
        printf("bitcount(255) = %d (expect 8)\n", bitcount(255));
        printf("bitcount(1023) = %d (expect 10)\n", bitcount(1023));
        printf("bitcount(0xFFFFFFFF) = %d (expect 32)\n", bitcount(0xFFFFFFFF));
        return 0;
}

/* x &= (x-1)
 * 1 is just 00000001
 * so x - 1 is x with the last 1 bit to 0, and 1 after it
 * &= that will set x & (x - 1), this set the last 1 to zero in x, the other 1 (x-1) are negated by the &
 */

int bitcount(unsigned x) {
        int b;

        for (b=0; x != 0; x &= x - 1)
                b++;
        return b;
}

