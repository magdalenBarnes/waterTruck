#include "DFRobot_GP8403.h" //include library for I2C modules
#include "I2CScanner.h" //include library to search for I2C modules

#include <NMEAGPS.h>

#define gpsPort Serial1 // just an alias, not a whole new variable

I2CScanner scanner; //create instance
NMEAGPS gps;
gps_fix fix;

DFRobot_GP8403 dac(&Wire,0x58); //Create instance of dac
DFRobot_GP8403 dac1(&Wire,0x59); //Create instance of dac 1
DFRobot_GP8403 dac2(&Wire,0x5A); //Create instance of dac 2

void setup() {

  Serial.begin(9600); //Begin serial communication with baud rate of 9600
  gpsPort.begin(9600);

  //While there is no serial communication print error message every second
  
  while(dac.begin()!=0){ 
    Serial.println("DAC0 init error");
    delay(1000);
   }
   
  while(dac1.begin()!=0){ 
    Serial.println("DAC1 init error");
    delay(1000);
   }

  //If there is serial communcication print success message 
  Serial.println("init succeed");

  scanner.Init(); //initiallize scanner
  scanner.Scan(); //scan for all I2C devices and addresses

 dac.setDACOutRange(dac.eOutputRange10V);//Set the output range as 0-10V for dac
 dac1.setDACOutRange(dac1.eOutputRange10V);//Set the output range as 0-10V for dac 1
 //dac2.setDACOutRange(dac2.eOutputRange10V);//Set the output range as 0-10V for dac 2
}

void loop(){

  fix = gps.read();
  Serial.print("latitude:");
  Serial.println( fix.latitude(), 6 ); // positive for N, negative for S
  Serial.print("longitude:");
  Serial.println( fix.longitude(), 6 ); // positive for E, negative for W 

  delay(5000);
 
  Serial.print("Voltage set to 10 V on all channels \n");

	dac.setDACOutVoltage(10000,2);//The DAC value for 3.5V output in OUT0 channel
  
  dac1.setDACOutVoltage(10000,2);//The DAC value for 3.5V output in OUT0 channel

  //dac2.setDACOutVoltage(10000,2);//The DAC value for 3.5V output in OUT0 channel

  delay(5000);

  Serial.print("Voltage set to 3 V on all channels \n");

  dac.setDACOutVoltage(3000,2);//The DAC value for 3.5V output in OUT0 channel

  dac1.setDACOutVoltage(3000,2);//The DAC value for 3.5V output in OUT0 channel

  //dac2.setDACOutVoltage(3000,2);//The DAC value for 3.5V output in OUT0 channel

  delay(5000);
 
  
  //dac.store(); //Save the set 3.5V voltage inside the chip


}