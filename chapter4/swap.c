#include <stdio.h>

#define swap(t, x, y) {\
        t temp = x;\
        x = y;\
        y = temp;\
}

int main(void) {
        int a = 5, b = 10;
        printf("before: a=%d b=%d\n", a, b);
        swap(int, a, b);
        printf("after:  a=%d b=%d (expect a=10 b=5)\n\n", a, b);

        double x = 3.14, y = 2.72;
        printf("before: x=%g y=%g\n", x, y);
        swap(double, x, y);
        printf("after:  x=%g y=%g (expect x=2.72 y=3.14)\n\n", x, y);

        char c1 = 'A', c2 = 'Z';
        printf("before: c1=%c c2=%c\n", c1, c2);
        swap(char, c1, c2);
        printf("after:  c1=%c c2=%c (expect c1=Z c2=A)\n\n", c1, c2);

        int arr[] = {100, 200};
        printf("before: arr[0]=%d arr[1]=%d\n", arr[0], arr[1]);
        swap(int, arr[0], arr[1]);
        printf("after:  arr[0]=%d arr[1]=%d (expect arr[0]=200 arr[1]=100)\n", arr[0], arr[1]);

        return 0;
}
