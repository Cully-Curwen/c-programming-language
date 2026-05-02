#include <ctype.h>
#include <stdio.h>

double atof(char s[]);
double ten_power(int n);

int main(void) {
        printf("atof(\"123.45\") = %g (expect 123.45)\n", atof("123.45"));
        printf("atof(\"123.45e-6\") = %g (expect 0.00012345)\n", atof("123.45e-6"));
        printf("atof(\"123.45e6\") = %g (expect 1.2345e+08)\n", atof("123.45e6"));
        printf("atof(\"123.45E2\") = %g (expect 12345)\n", atof("123.45E2"));
        printf("atof(\"-1.5e3\") = %g (expect -1500)\n", atof("-1.5e3"));
        printf("atof(\"1.0e-3\") = %g (expect 0.001)\n", atof("1.0e-3"));
        printf("atof(\"1.0e+3\") = %g (expect 1000)\n", atof("1.0e+3"));
        printf("atof(\"42\") = %g (expect 42)\n", atof("42"));
        printf("atof(\".5e2\") = %g (expect 50)\n", atof(".5e2"));
        printf("atof(\"0.0\") = %g (expect 0)\n", atof("0.0"));
        return 0;
}

/* atof: convert string s to double */
double atof(char s[]) {
        double val, power, exp;
        int i, sign, expSign;

        for (i = 0; isspace(s[i]); i++) /* skip white space */
                ;
        sign = (s[i] == '-') ? -1 : 1;
        if (s[i] == '+' || s[i] == '-')
                i++;
        for (val = 0.0; isdigit(s[i]); i++)
                val = 10.0 * val + (s[i] - '0');
        if (s[i] == '.')
                i++;
        for (power = 1.0; isdigit(s[i]); i++) {
                val = 10.0 * val + (s[i] - '0');
                power *= 10.0;
        }
        if (s[i] == 'e' || s[i] == 'E')
                i++;
        expSign = (s[i] == '-') ? -1 : 1;
        if (s[i] == '+' || s[i] == '-')
                i++;
        for (exp = 0.0;isdigit(s[i]); i++)
                exp = 10.0 * exp + (s[i] - '0');
        return sign * (val / power) * ten_power(expSign * exp);
}

/* 10toPower: */
double ten_power(int n) {
        int i;
        double d;

        d = 1.0;
        if (n >= 0)
                for (i=0; i < n; i++)
                        d *= 10.0;
        else
                for (i=0; i > n; i--)
                        d /= 10.0;
        return d;
}

