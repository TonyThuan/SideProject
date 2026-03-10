#include <main.h>

void main()
{

   while(TRUE)
   {
      //TODO: User Code
      OUTPUT_HIGH(PIN_D0);
      delay_ms(1000);
      OUTPUT_low(PIN_D0);
      delay_ms(1000);
   }

}
