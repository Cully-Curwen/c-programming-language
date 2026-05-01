#include <limits.h>
#include <stdio.h>

unsigned rightrot(unsigned x, int n);

int main(void) {
        /* rightrot(x, n)
         * x = 170 = 10101010, rotate right by 2
         * bottom 2 bits (10) move to top
         */
        printf("rightrot(170, 2) = %u (expect 2147483690)\n", rightrot(170, 2));

        /* x = 1 = 00000001, rotate right by 1
         * bottom bit wraps to top
         * result: 10000000000000000000000000000000 = 2147483648
         */
        printf("rightrot(1, 1) = %u (expect %u)\n", rightrot(1, 1), 1u << 31);

        /* x = 15 = 00001111, rotate right by 4
         * bottom 4 bits (1111) wrap to top
         * result: 11110000000000000000000000001111 >> wait no
         * result: 11110000000000000000000000000000 = 4026531840
         */
        printf("rightrot(15, 4) = %u (expect %u)\n", rightrot(15, 4), 15u << 28);

        /* x = 137 = 10001001, rotate right by 1
         * bottom bit (1) wraps to top
         * result: 10000000000000000000000001000100 = 2147483716
         */
        printf("rightrot(137, 1) = %u (expect %u)\n", rightrot(137, 1), (137u >> 1) | (1u << 31));

        /* rotate by 0 — should return unchanged */
        printf("rightrot(170, 0) = %u (expect 170)\n", rightrot(170, 0));

        /* full rotation — rotate by 32 should return unchanged */
        printf("rightrot(170, 32) = %u (expect 170)\n", rightrot(170, 32));

        return 0;
}

unsigned rightrot(unsigned x, int n) {
        /* get sizeof unsigned
         * get set of n 1 bits
         * AND x with set
         * left shitf sizeof - n
         * right shift x by n
         * OR set with x
         */
        return ((x & ~(~0 << n)) << (sizeof(unsigned) * CHAR_BIT - n)) | (x >> n);
}
