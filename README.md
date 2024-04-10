# Water Truck Arm Senior Design
This GitHub page contains the two codes created for the 2023-2024 senior design project. The members of this project were Maggie Barnes, Elyssa Roberts, and TJ Wink. The two codes include one demonstration code and one on-site code for use at a horse racetrack. The two codes are explained below, however the code files are commented for more information as well. For complete documentation of the project, refer to the senior design website.

## Demonstration Code
Three premade libraries were included in the code. The libraries contained functions to operate the I2C DACs, scan for available I2C communication, and read the GPS.
```c
#include "DFRobot_GP8403.h"
#include "I2CScanner.h"
#include <NMEAGPS.h>
```
The Arduino Mega contains several serial ports. The serial port designated to the GPS was renamed "gpsPort".
```c
#define gpsPort Serial1
```
Three variables and their classes were defined based on the premade libraries.
```c
I2CScanner scanner; //create variable of scanner, class I2C scanner
NMEAGPS gps; // create variable gps, class NMEA gps
gps_fix fix; // create variable fix, class gps_fix
```
Instances were made of the three I2C DACs to later call on.
```c
DFRobot_GP8403 dac(&Wire,0x58);
DFRobot_GP8403 dac1(&Wire,0x59);
DFRobot_GP8403 dac2(&Wire,0x5A);
```
In the setup loop serial communication was initiated with the computer serial port and the gps port
```c
void setup() {

  Serial.begin(9600);
  gpsPort.begin(9600);
```
To initalize the I2C DACs, a begin function was called from the DAC library which outputs an error code if initialization fails. If the error code was not zero, an error message displays. If the code returned was zero, a message was displayed indicating successful initialization. The initalization was completed for each I2C DAC, example code for one is shown below.
```c
while(dac.begin()!=0){ 
    Serial.println("DAC0 init error"); 
    delay(1000); 
   }
Serial.println("DAC init succeed");
```
To choose the voltage range of the I2C DAC to be 0 - 10 V, the command "dac.setDACOutRange" was used.

 dac.setDACOutRange(dac.eOutputRange10V);//Set the output range as 0-10V for dac
