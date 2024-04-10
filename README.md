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
I2CScanner scanner; 
NMEAGPS gps;
gps_fix fix; 
```
Instances of three I2C DACs were made to call later on.
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
To initalize the I2C DACs, a begin function was called from the DAC library which outputed an error code if initialization fails. If the error code was not zero, an error message displayed. If the code returned was zero, a message was displayed indicating successful initialization. The "dac" at the beginning of the "dac.begin" was adjusted to "dac1" and "dac2" to refernce the other two I2C DACs. The initalization was completed for each I2C DAC, example code for one is shown below.
```c
while(dac.begin()!=0){ 
    Serial.println("DAC0 init error"); 
    delay(1000); 
   }
Serial.println("DAC init succeed");
```
To choose the voltage range of the I2C DAC to be 0 - 10 V, the command "dac.setDACOutRange" was used. The "dac" at the beginning of the "dac.DACOutRange" was adjusted to "dac1" and "dac2" to refernce the other two I2C DACs. The output range selection was completed for each I2C DAC, example code for one is shown below.
```c
 dac.setDACOutRange(dac.eOutputRange10V);
```
The main body loop starts by reading the gps and printing the latitude and longitude measured. First, the GPS was read using the "gps.read()" command and set equal to the variable "fix". The variable was then printed in the serial monitor using the "Serial.print()" command.
```c
void loop(){

  fix = gps.read();

  Serial.print("latitude:"); 
  Serial.println( fix.latitude(), 6 );
  Serial.print("longitude:");
  Serial.println( fix.longitude(), 6 ); 
```
Because the demonstration took place inside, the GPS could only read (0,0). To incorporate this into the system an if statement comparing the longitude to zero was created to act as a barrier into the valve operation code.
```c
 if (fix.longitude() == 0) {
```
If the condition was met, the Arduino would communicate to the I2C DACs to change voltage and display a message on the serial monitor. First, the serial monitor displayed "break" to indicate the valves were closed. The voltage to all valves was set to zero using the "dac.setDACOutVoltage(<#>,<#>) command, where the first number input was the voltage level between 0 - 10000 (0 is 0 V, and 10000 is 10 V), and the second number was the channel of the DAC. A delay was set to hold the voltage at zero. Next, the a message was displayed to indicate the truck was traveling straight. The voltages were all set to 3000 (3V). Another delay followed. The valves were all set to zero again. Finally, all valves were set to a value between 1300 and 1700 (1.3 V - 1.7 V). The changes in voltages were completed for each I2C DAC, example code for one is shown below.

```c
Serial.print("break \n"); 
dac.setDACOutVoltage(0,0);
delay(30000); 

Serial.print("Going on straightaway \n");
dac.setDACOutVoltage(3000,0);
delay(30000); 

Serial.print("Going around corner \n");
dac.setDACOutVoltage(1300,0);
delay(20000);//wait 20 seconds

Serial.print("break \n"); 
dac.setDACOutVoltage(0,0);
```
 
## On-Site Code
The code for on-site operation is similar to the demonstration code. The differences between the two are highlighted below.

After the inclusion of libraries, the coordinates to create boxes on the horse racetrack were defined as floating point variables. See the senior design website for explanation of the box system. In addtion, floating point variables were created to hold the latitude and longitude values. 
```c
float ALowerBound = 38.0433178;
float AUpperBound = 38.0451909;
float ALeftBound = -84.6083267;
float ARightBound = -84.6054986;

float BLowerBound = 38.0473288;
float BUpperBound = 38.0492728;
float BLeftBound = -84.6114853;
float BRightBound = -84.6091066;

float CurrentLat;
float CurrentLong;
```

Next, if the GPS was able to communicate with the Arduino, the latitude and longitude were printed on the serial monitor similar to the demonstration code. The values for latitude and longitude were stored in variable to use later.
```c
  if (gps.available( gpsPort )) { 
    fix = gps.read();

    Serial.println( fix.latitude(), 6 ); 
    Serial.println( fix.longitude(), 6 ); 
     CurrentLat = fix.latitude(); 
     CurrentLong = fix.longitude(); 
```

A series of if, else if, and else statements were used to determine where the truck was on the track. If the coordiantes were in box A or box B, a message would display to indicate the truck was rounding a curve. In addition, the voltages to the valves were changed to varying voltages using the same commands as in the demonstration code. If the truck was not in either box, a message displayed that the truck was going around a straight away. In the case of a straightaway, all voltages were set to 3000 (3V).
```c
if (CurrentLong >= ALeftBound & CurrentLong <= ARightBound & CurrentLat >= ALowerBound & CurrentLat <= AUpperBound) {
    Serial.print("Going around curve A \n"); 

else if (CurrentLong >= BLeftBound & CurrentLong <= BRightBound & CurrentLat >= BLowerBound & CurrentLat <=     BUpperBound) {
    Serial.print("Going around curve B \n"); /

else
    Serial.print("Going on straightaway \n");
```
At the end of each if, else if, and else statement the current latitude and longitude were reread and saved into variable. The rereading of coordinates ensured the system would keep repeating itself and adjusting for changes in location.
```c
 fix = gps.read();
 CurrentLat = fix.latitude(); S
 CurrentLong = fix.longitude(); 
```
