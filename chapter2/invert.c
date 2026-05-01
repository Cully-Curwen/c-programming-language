#include <stdio.h>

unsigned invert(unsigned x, int p, int n);

int main(void) {
        /* invert(x, p, n)
         * x = 170 = 10101010, invert 3 bits at position 4
         * bits 4-2: 010 → 101
         * result: 10110110 = 182
         */
        printf("invert(170, 4, 3) = %u (expect 182)\n", invert(170, 4, 3));

        /* x = 255 = 11111111, invert 4 bits at position 5
         * bits 5-2: 1111 → 0000
         * result: 11000011 = 195
         */
        printf("invert(255, 5, 4) = %u (expect 195)\n", invert(255, 5, 4));

        /* x = 0 = 00000000, invert 3 bits at position 7
         * bits 7-5: 000 → 111
         * result: 11100000 = 224
         */
        printf("invert(0, 7, 3) = %u (expect 224)\n", invert(0, 7, 3));

        /* x = 255 = 11111111, invert 2 bits at position 1
         * bits 1-0: 11 → 00
         * result: 11111100 = 252
         */
        printf("invert(255, 1, 2) = %u (expect 252)\n", invert(255, 1, 2));

        /* x = 0 = 00000000, invert 8 bits at position 7
         * all bits: 00000000 → 11111111
         * result: 11111111 = 255
         */
        printf("invert(0, 7, 8) = %u (expect 255)\n", invert(0, 7, 8));

        /* x = 170 = 10101010, invert 1 bit at position 0
         * bit 0: 0 → 1
         * result: 10101011 = 171
         */
        printf("invert(170, 0, 1) = %u (expect 171)\n", invert(170, 0, 1));

        return 0;
}

unsigned invert(unsigned x, int p, int n) {
        /* get n 1 bits shifted by p
         * xor x by set
         */
        return x ^ ~(~0 << n) << (p + 1 - n);
}
