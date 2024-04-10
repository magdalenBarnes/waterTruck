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
To initalize the I2C DACs, a begin function was called from the DAC library which outputs an error code if initialization fails. If the error code was not zero, an error message displays. If the code returned was zero, a message was displayed indicating successful initialization. The "dac" at the beginning of the "dac.begin" was adjusted to "dac1" and "dac2" to refernce the other two I2C DACs. The initalization was completed for each I2C DAC, example code for one is shown below.
```c
while(dac.begin()!=0){ 
    Serial.println("DAC0 init error"); 
    delay(1000); 
   }
Serial.println("DAC init succeed");
```
To choose the voltage range of the I2C DAC to be 0 - 10 V, the command "dac.setDACOutRange" was used. The "dac" at the beginning of the "dac.begin" was adjusted to "dac1" and "dac2" to refernce the other two I2C DACs. The initalization was completed for each I2C DAC, example code for one is shown below.
```c
 dac.setDACOutRange(dac.eOutputRange10V);//Set the output range as 0-10V for dac
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
If the condition was met, the Arduino would communicate to the I2C DACs to change voltage and display a message on the serial monitor.
```c
Serial.print("break \n"); //print message indicating break in valve operation, voltage change to 0V
dac.setDACOutVoltage(0,0);//Set the voltage of dac channel 0 (valve 1) to 0 V
delay(30000); //wait 30 seconds

Serial.print("Going on straightaway \n"); //print message indicating straightaway, voltage change to 3V
dac.setDACOutVoltage(3000,0);//Set the voltage of dac channel 0 (valve 1) to 3 V
delay(30000); //wait 30 seconds

Serial.print("Going around corner \n"); //print message indicating voltage change to range of 1.3-1.7V
dac.setDACOutVoltage(1300,0);//Set the voltage of dac channel 0 (valve 1) to 1.3 V
delay(20000);//wait 20 seconds


Serial.print("break \n"); //print message indicating break in valve operation, voltage change to 0V
dac.setDACOutVoltage(0,0);//Set the voltage of dac channel 0 (valve 1) to 0 V
```
