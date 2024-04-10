//Parts of code from: 
//https://forum.arduino.cc/t/connecting-arduino-due-to-gps-neo-6m/488863/3


#include <NMEAGPS.h> //Include library

#define gpsPort Serial1 // just an alias, not a whole new variable

#include "DFRobot_GP8403.h" //include library for I2C modules

NMEAGPS gps; 
gps_fix fix;

DFRobot_GP8403 dac(&Wire,0x58); //Create instance of dac at address 0x58 on outside
DFRobot_GP8403 dac1(&Wire,0x59); //Create instance of dac 1 at address 0x59
DFRobot_GP8403 dac2(&Wire,0x5A); //Create instance of dac 2 at address 0x5A closest to center

//Create variables to hold coordinate values to create box A

//Define coordinate values to create box A
float ALowerBound = 38.0433178;
float AUpperBound = 38.0451909;
float ALeftBound = -84.6083267;
float ARightBound = -84.6054986;

//Define coordinate values to create box B
float BLowerBound = 38.0473288;
float BUpperBound = 38.0492728;
float BLeftBound = -84.6114853;
float BRightBound = -84.6091066;

//define variables to hold coordinates
float CurrentLat;
float CurrentLong;

void  setup()
{
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

 dac.setDACOutRange(dac.eOutputRange10V);//Set the output range as 0-10V for dac
 dac1.setDACOutRange(dac1.eOutputRange10V);//Set the output range as 0-10V for dac 1
 dac2.setDACOutRange(dac2.eOutputRange10V);//Set the output range as 0-10V for dac 2
}


void loop()
{
  if (gps.available( gpsPort )) { //if GPS can communicate read GPS coordinates
    fix = gps.read();

    Serial.println( fix.latitude(), 6 ); // positive for N, negative for S
    Serial.println( fix.longitude(), 6 ); // positive for E, negative for W

     CurrentLat = fix.latitude(); //define current latitude as latitude read by GPS
     CurrentLong = fix.longitude(); //define current longitude as longitude read by GPS

  //If the coordinates are both within bounds of box A
  if (CurrentLong >= ALeftBound & CurrentLong <= ARightBound & CurrentLat >= ALowerBound & CurrentLat <= AUpperBound) {
    Serial.print("Going around curve A \n"); //print message indicating voltage change to range of 1.3-1.7V
   

      dac.setDACOutVoltage(1300,0);//Set the voltage of dac channel 0 (valve 1) to 1.3 V

      dac.setDACOutVoltage(1400,1);//Set the voltage of dac channel 1 (valve 2) to 1.4V

      dac1.setDACOutVoltage(1500,0);//Set the voltage of dac1 channel 0 (valve 3) to 1.5 V

      dac1.setDACOutVoltage(1600,1);//Set the voltage of dac1 channel 0 (valve 4) to 1.6 V

      dac2.setDACOutVoltage(1700,0);//Set the voltage of dac2 channel 0 (valve 5) to 1.7 V

       fix = gps.read();
            CurrentLat = fix.latitude(); //define current latitude as latitude read by GPS
            CurrentLong = fix.longitude(); //define current longitude as longitude read by GPS

  }
  //If the coordinates are both within bounds of box B
  else if (CurrentLong >= BLeftBound & CurrentLong <= BRightBound & CurrentLat >= BLowerBound & CurrentLat <= BUpperBound) {
    Serial.print("Going around curve B \n"); //print message indicating voltage change to range of 1.3-1.7V
    

      dac.setDACOutVoltage(1300,0);//Set the voltage of dac channel 0 (valve 1) to 1.3 V

      dac.setDACOutVoltage(1400,1);//Set the voltage of dac channel 1 (valve 2) to 1.4V

      dac1.setDACOutVoltage(1500,0);//Set the voltage of dac1 channel 0 (valve 3) to 1.5 V

      dac1.setDACOutVoltage(1600,1);//Set the voltage of dac1 channel 0 (valve 4) to 1.6 V

      dac2.setDACOutVoltage(1700,0);//Set the voltage of dac2 channel 0 (valve 5) to 1.7 V

       fix = gps.read();
            CurrentLat = fix.latitude(); //define current latitude as latitude read by GPS
            CurrentLong = fix.longitude(); //define current longitude as longitude read by GPS

  }
  //If the coordinates are not within box A or B
  else

    Serial.print("Going on straightaway \n");//print message indicating straightaway, voltage change to 3V
     

      dac.setDACOutVoltage(3000,0);//Set the voltage of dac channel 0 (valve 1) to 3 V

      dac.setDACOutVoltage(3000,1);//Set the voltage of dac channel 1 (valve 2) to 3 V

      dac1.setDACOutVoltage(3000,0);//Set the voltage of dac1 channel 0 (valve 3) to 3 V

      dac1.setDACOutVoltage(3000,1);//Set the voltage of dac1 channel 1 (valve 4) to 3 V

      dac2.setDACOutVoltage(3000,0);//Set the voltage of dac2 channel 0 (valve 5) to 3 V

       fix = gps.read();
            CurrentLat = fix.latitude(); //define current latitude as latitude read by GPS
            CurrentLong = fix.longitude(); //define current longitude as longitude read by GPS
  }
}
