#include <stdio.h>

/* Fahrenheit-Celsius temperature table desending
    from Fahr = 300, 280, ...., 0 */

main()
{
  int fahr;
  printf("Fahrenheit-Celsius Desending\n");
  for(fahr = 300; fahr >= 0; fahr = fahr - 20) {
    printf("%3d %6.1f\n", fahr, (5.0 / 9.0) * ( fahr - 32));
  }
}
