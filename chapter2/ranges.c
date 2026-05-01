#include <stdio.h>
#include <limits.h>
#include <float.h>

short two_tothe_short(short n);
long two_tothe_long(long n);

int main(void) {
        printf("Char storage sizes:\n");
        printf("  CHAR_BIT  = %d bits\n", CHAR_BIT);
        printf("Char (plain — signed or unsigned):\n");
        printf("  CHAR_MIN  = %d\n", CHAR_MIN);
        printf("  CHAR_MAX  = %d\n", CHAR_MAX);
        printf("Signed char:\n");
        printf("  SCHAR_MIN = %d\n", SCHAR_MIN);
        printf("  SCHAR_MAX = %d\n", SCHAR_MAX);
        printf("Unsigned char:\n");
        printf("  UCHAR_MAX = %u\n", UCHAR_MAX);
        printf("\n");
        printf("Short: %lu Bytes (%lu bits)\n", sizeof(short), sizeof(short) * CHAR_BIT);
        printf("  SHRT_MIN  = %d\n", SHRT_MIN);
        printf("  SHRT_MAX  = %d\n", SHRT_MAX);
        printf("Unsigned short:\n");
        printf("  USHRT_MAX = %u\n", USHRT_MAX);
        printf("\n");
        printf("Int: %lu Bytes (%lu bits)\n", sizeof(int), sizeof(int) * CHAR_BIT);
        printf("  INT_MIN   = %d\n", INT_MIN);
        printf("  INT_MAX   = %d\n", INT_MAX);
        printf("Unsigned int:\n");
        printf("  UINT_MAX  = %u\n", UINT_MAX);
        printf("\n");
        printf("Long: %lu Bytes (%lu bits)\n", sizeof(long), sizeof(long) * CHAR_BIT);
        printf("  LONG_MIN  = %ld\n", LONG_MIN);
        printf("  LONG_MAX  = %ld\n", LONG_MAX);
        printf("Unsigned long:\n");
        printf("  ULONG_MAX = %lu\n", ULONG_MAX);
        printf("\n");

        printf("* note to self, there is no Unsiged minimun as they are all 0");
        printf("\n");
        printf("\n");


        printf("Manual calculations\n");
        int i;
        short s;
        long l;

        if (((s=0) - 1) > 0) {
                printf("unsigned short max: %d\n", s - 1);
        } else {
                for (s=0; (two_tothe_short(s)) > 0; ++s);
                short max = (two_tothe_short(s-1) - 1 + two_tothe_short(s-1));
                printf("signed short min: %d\n", (-max - 1));
                printf("signed short max: %d\n", max);
        }

        if (((i=0) - 1) > 0) {
                printf("unsigned int max: %d\n", i - 1);
        } else {
                for (i=0; (1 << i) > 0; ++i);
                int max = (1 << (i - 1)) - 1 + (1 << (i - 1));
                printf("signed int min: %d\n", (-max - 1));
                printf("signed int max: %d\n", max);
        }

        if (((l=0) - 1) > 0) {
                printf("unsigned long max: %ld\n", l - 1);
        } else {
                for (l=0; (two_tothe_long(l)) > 0; ++l);
                long max = (two_tothe_long(l-1) - 1 + two_tothe_long(l-1));
                printf("signed long min: %ld\n", (-max - 1));
                printf("signed long max: %ld\n", max);
        }

        printf("\nFloating Point\n");
        printf("\n");

        printf("Float: %zu bytes (%zu bits)\n", sizeof(float), sizeof(float) * CHAR_BIT);
        printf("  FLT_MIN      = %e\n", FLT_MIN);
        printf("  FLT_MAX      = %e\n", FLT_MAX);
        printf("  FLT_MAX      = %f\n", FLT_MAX);
        printf("  FLT_DIG      = %d\n", FLT_DIG);
        printf("  FLT_EPSILON  = %e\n", FLT_EPSILON);
        printf("  FLT_MANT_DIG = %d\n", FLT_MANT_DIG);
        printf("  FLT_MIN_EXP  = %d\n", FLT_MIN_EXP);
        printf("  FLT_MAX_EXP  = %d\n", FLT_MAX_EXP);
        printf("\n");

        printf("Double: %zu bytes (%zu bits)\n", sizeof(double), sizeof(double) * CHAR_BIT);
        printf("  DBL_MIN      = %e\n", DBL_MIN);
        printf("  DBL_MAX      = %e\n", DBL_MAX);
        printf("  DBL_MAX      = %f\n", DBL_MAX);
        printf("  DBL_DIG      = %d\n", DBL_DIG);
        printf("  DBL_EPSILON  = %e\n", DBL_EPSILON);
        printf("  DBL_MANT_DIG = %d\n", DBL_MANT_DIG);
        printf("  DBL_MIN_EXP  = %d\n", DBL_MIN_EXP);
        printf("  DBL_MAX_EXP  = %d\n", DBL_MAX_EXP);
        printf("\n");

        printf("Long Double: %zu bytes (%zu bits)\n", sizeof(long double), sizeof(long double) * CHAR_BIT);
        printf("  LDBL_MIN      = %Le\n", LDBL_MIN);
        printf("  LDBL_MAX      = %Le\n", LDBL_MAX);
        printf("  LDBL_MAX      = %Lf\n", LDBL_MAX);
        printf("  LDBL_DIG      = %d\n", LDBL_DIG);
        printf("  LDBL_EPSILON  = %Le\n", LDBL_EPSILON);
        printf("  LDBL_MANT_DIG = %d\n", LDBL_MANT_DIG);
        printf("  LDBL_MIN_EXP  = %d\n", LDBL_MIN_EXP);
        printf("  LDBL_MAX_EXP  = %d\n", LDBL_MAX_EXP);
        printf("\n");

        printf("* note e in float values is 10^ not euler's number");
}

short two_tothe_short(short n) {
        short p = 1;
        short i;

        for (i = 0; i < n; ++i) {
                p = p * 2;
        }
        return p;
}

long two_tothe_long(long n) {
        long p = 1;
        long i;

        for (i = 0; i <= n; ++i) {
                p = p * 2;
        }
        return p;
}
