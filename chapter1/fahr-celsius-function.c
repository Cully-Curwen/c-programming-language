#include <stdio.h>

/* print Fahrenheit-Celsius table, floating-point version with table heading */

float fahrToCelsius (float fahr) {
        return (5.0 / 9.0) * (fahr - 32.0);
}

int main(void)
{
  float fahr;
  int lower, upper, step;

  lower = 0;      /* lower limit of temperature table */
  upper = 300;    /* upper limit */
  step = 20;      /* step size */

  printf("Fahrenheit-Celsius table\n");

  fahr = lower;
  while (fahr < upper) {
    printf("%3.0f %6.1f\n", fahr, fahrToCelsius(fahr));
    fahr = fahr + step;
  }
}
