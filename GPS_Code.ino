#include <NMEAGPS.h>

#define gpsPort Serial1 // just an alias, not a whole new variable

NMEAGPS gps;
gps_fix fix;

void  setup()
{
    Serial.begin( 9600 );
    gpsPort.begin( 9600 );
}

void loop()
{
  if (gps.available( gpsPort )) {
    fix = gps.read();

    Serial.println( fix.latitude(), 6 ); // positive for N, negative for S
    Serial.println( fix.longitude(), 6 ); // positive for E, negative for W
  }
}