#include <stdio.h>

unsigned setbits(unsigned x, int p, int n, unsigned y);

int main(void) {
        /* setbits(x, p, n, y)
         * x = 170 = 10101010
         * set 3 bits starting at position 4 to rightmost 3 bits of y = 7 (111)
         * bits 4-2 of x: 010 → replaced with 111
         * result: 10111110 = 190
         */
        printf("setbits(170, 4, 3, 7) = %u (expect 190)\n", setbits(170, 4, 3, 7));

        /* x = 255 = 11111111, replace 4 bits at position 5 with bottom 4 of y = 0
         * bits 5-2: 1111 → 0000
         * result: 11000011 = 195
         */
        printf("setbits(255, 5, 4, 0) = %u (expect 195)\n", setbits(255, 5, 4, 0));

        /* x = 0 = 00000000, set 3 bits at position 7 from y = 5 (101)
         * bits 7-5: 000 → 101
         * result: 10100000 = 160
         */
        printf("setbits(0, 7, 3, 5) = %u (expect 160)\n", setbits(0, 7, 3, 5));

        /* x = 0xFF = 11111111, set 2 bits at position 1 from y = 0
         * bits 1-0: 11 → 00
         * result: 11111100 = 252
         */
        printf("setbits(255, 1, 2, 0) = %u (expect 252)\n", setbits(255, 1, 2, 0));

        /* no change case: x = 170 = 10101010, set 3 bits at position 4 from y = 2 (010)
         * bits 4-2 of x are already 010
         * result: 10101010 = 170
         */
        printf("setbits(170, 4, 3, 2) = %u (expect 170)\n", setbits(170, 4, 3, 2));

        /* x = 0, set 8 bits at position 7 from y = 0xAB = 10101011
         * all 8 bits replaced
         * result: 10101011 = 171
         */
        printf("setbits(0, 7, 8, 171) = %u (expect 171)\n", setbits(0, 7, 8, 171));

        return 0;
}

unsigned setbits(unsigned x, int p, int n, unsigned y) {
        /* set n bits at bit p in x to 0
         * get just n bits from right, shift to p
         * or the 2 sets
         */
        return (x & ~(~(~0 << n) << (p + 1 - n))) | ((y & ~(~0 << n)) << (p + 1 - n));
}
