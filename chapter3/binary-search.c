#include <stdio.h>

int binsearch(int x, int v[], int n);

int main(void) {
        int v[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
        int n = 10;

        printf("search 1  = %d (expect 0)\n", binsearch(1, v, n));
        printf("search 19 = %d (expect 9)\n", binsearch(19, v, n));
        printf("search 11 = %d (expect 5)\n", binsearch(11, v, n));
        printf("search 7  = %d (expect 3)\n", binsearch(7, v, n));
        printf("search 2  = %d (expect -1)\n", binsearch(2, v, n));
        printf("search 0  = %d (expect -1)\n", binsearch(0, v, n));
        printf("search 20 = %d (expect -1)\n", binsearch(20, v, n));
        printf("search 10 = %d (expect -1)\n", binsearch(10, v, n));
        return 0;
}

int binsearch(int x, int v[], int n) {
        int low, high, mid;

        low = 0;
        high = n - 1;

        while (low < high) {
                mid = (low + high) / 2;
                (x <= v[mid]) ? (high = mid) : (low = mid + 1);
        }

        if (v [low] == x)
                return low;
        else
                return -1;
}
