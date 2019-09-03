#include <stdio.h>

/* print Celsius-Fahrenheit table
    for celsius = 0, 10, ...., 100; */

main()
{
  float celsius, fahr;
  int lower, upper, step;

  lower = 0;      /* lower limit of temperature table */
  upper = 100;    /* upper limit */
  step = 10;      /* step size */

  printf("Celsius to Fahrenheit\n");

  celsius = lower;
  while (celsius <= upper){
    fahr = celsius * (9.0 / 5.0) + 32.0;
    printf("%3.0f %6.1f\n", celsius, fahr);
    celsius = celsius + step;
  }
}
