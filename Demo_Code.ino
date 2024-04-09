//DEMONSTRATION CODE

#include "DFRobot_GP8403.h" //include library for I2C modules
#include "I2CScanner.h" //include library to search for I2C modules

#include <NMEAGPS.h> // include library for GPS

#define gpsPort Serial1 // just an alias, not a whole new variable

I2CScanner scanner; //create variable of scanner, class I2C scanner
NMEAGPS gps; // create variable gps, class NMEA gps
gps_fix fix; // create variable fix, class gps_fix

DFRobot_GP8403 dac(&Wire,0x58); //Create instance of dac at address 0x58 on outside
DFRobot_GP8403 dac1(&Wire,0x59); //Create instance of dac 1 at address 0x59
DFRobot_GP8403 dac2(&Wire,0x5A); //Create instance of dac 2 at address 0x5A closest to center

//setup runs once
void setup() {

  Serial.begin(9600); //Begin serial communication with computer at baud rate of 9600
  gpsPort.begin(9600); // Begin serial communication with GPS at baud rate of 9600

 //while the initialization procedure of the DACs is not zero, print error message
  
  while(dac.begin()!=0){  //while 0 is not returned
    Serial.println("DAC0 init error"); //print error message
    delay(1000); //wait one second then repeat 
   }
   
  while(dac1.begin()!=0){  //while 0 is not returned 
    Serial.println("DAC1 init error"); //print error message
    delay(1000); //wait one second then repeat 
   }

  while(dac2.begin()!=0){  //while 0 is not returned 
    Serial.println("DAC1 init error"); //print error message
    delay(1000); //wait one second then repeat 
   }

  //If the DACs initialize properly
  Serial.println("DAC init succeed");

  scanner.Init(); //initiallize scanner
  scanner.Scan(); //scan for all I2C devices and addresses

 dac.setDACOutRange(dac.eOutputRange10V);//Set the output range as 0-10V for dac
 dac1.setDACOutRange(dac1.eOutputRange10V);//Set the output range as 0-10V for dac 1
 dac2.setDACOutRange(dac2.eOutputRange10V);//Set the output range as 0-10V for dac 2
}

//start loop
void loop(){

  fix = gps.read(); //read gps and set the reading to fix

  //print latitude and longitude coordinates
  Serial.print("latitude:"); 
  Serial.println( fix.latitude(), 6 ); // positive for N, negative for S 
  Serial.print("longitude:");
  Serial.println( fix.longitude(), 6 ); // positive for E, negative for W 

//if the GPS reads (0,0) begin valve control
  if (fix.longitude() == 0) {
    
  Serial.print("break \n"); //print message indicating break in valve operation, voltage change to 0V

  dac.setDACOutVoltage(0,0);//Set the voltage of dac channel 0 (valve 1) to 0 V

  dac.setDACOutVoltage(0,1);//Set the voltage of dac channel 1 (valve 2) to 0 V 

  dac1.setDACOutVoltage(0,0);//Set the voltage of dac1 channel 0 (valve 3) to 0 V

  dac1.setDACOutVoltage(0,1);//Set the voltage of dac1 channel 1 (valve 4) to 0 V

  dac2.setDACOutVoltage(0,0);//Set the voltage of dac2 channel 0 (valve 5) to 0 V


  delay(30000); //wait 30 seconds


 
  Serial.print("Going on straightaway \n"); //print message indicating straightaway, voltage change to 3V

  dac.setDACOutVoltage(3000,0);//Set the voltage of dac channel 0 (valve 1) to 3 V

  dac.setDACOutVoltage(3000,1);//Set the voltage of dac channel 1 (valve 2) to 3 V

  dac1.setDACOutVoltage(3000,0);//Set the voltage of dac1 channel 0 (valve 3) to 3 V

  dac1.setDACOutVoltage(3000,1);//Set the voltage of dac1 channel 1 (valve 4) to 3 V

  dac2.setDACOutVoltage(3000,0);//Set the voltage of dac2 channel 0 (valve 5) to 3 V

  

  delay(20000);//wait 20 seconds


  Serial.print("break \n"); //print message indicating break in valve operation, voltage change to 0V

  dac.setDACOutVoltage(0,0);//Set the voltage of dac channel 0 (valve 1) to 0 V

  dac.setDACOutVoltage(0,1);//Set the voltage of dac channel 1 (valve 2) to 0 V 

  dac1.setDACOutVoltage(0,0);//Set the voltage of dac1 channel 0 (valve 3) to 0 V

  dac1.setDACOutVoltage(0,1);//Set the voltage of dac1 channel 1 (valve 4) to 0 V

  dac2.setDACOutVoltage(0,0);//Set the voltage of dac2 channel 0 (valve 5) to 0 V


  delay(30000); //wait 30 seconds



  Serial.print("Going around corner \n"); //print message indicating voltage change to range of 1.3-1.7V

  dac.setDACOutVoltage(1300,0);//Set the voltage of dac channel 0 (valve 1) to 1.3 V

  dac.setDACOutVoltage(1400,1);//Set the voltage of dac channel 1 (valve 2) to 1.4V

  dac1.setDACOutVoltage(1500,0);//Set the voltage of dac1 channel 0 (valve 3) to 1.5 V

  dac1.setDACOutVoltage(1600,1);//Set the voltage of dac1 channel 0 (valve 4) to 1.6 V

  dac2.setDACOutVoltage(1700,0);//Set the voltage of dac2 channel 0 (valve 5) to 1.7 V

 

  delay(20000);//wait 20 seconds


  Serial.print("break \n"); //print message indicating break in valve operation, voltage change to 0V

  dac.setDACOutVoltage(0,0);//Set the voltage of dac channel 0 (valve 1) to 0 V

  dac.setDACOutVoltage(0,1);//Set the voltage of dac channel 1 (valve 2) to 0 V 

  dac1.setDACOutVoltage(0,0);//Set the voltage of dac channel 0 (valve 3) to 0 V

  dac1.setDACOutVoltage(0,1);//Set the voltage of dac channel 1 (valve 4) to 0 V

  dac2.setDACOutVoltage(0,0);//Set the voltage of dac channel 0 (valve 5) to 0 V


  delay(30000); //wait 30 seconds
 

  }

}