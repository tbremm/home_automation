// Makes the LED blink
// LED plugs into physical pin #17 (wiringPi pin 0)

#include <wiringPi.h>
#include <stdio.h>

int main (void)
{
  wiringPiSetup () ;
  pinMode (0, OUTPUT) ;
  for (;;)
  {
    digitalWrite (0, HIGH) ; delay (500) ;
    digitalWrite (0,  LOW) ; delay (500) ;
  }
  return 0 ;
}
