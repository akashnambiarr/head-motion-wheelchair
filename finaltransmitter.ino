 const int xPin = 0;
const int yPin = 1;
const int zPin = 2;
//The minimum and maximum values that came from
//the accelerometer while standing still
//You very well may need to change these
int minVal = 265;
int maxVal = 402;


//to hold the caculated values
double x;
double y;
double z;

#include "VirtualWire.h"


void setup(){
 //initialize seial communications at 9600 bps
Serial.begin(9600);
  vw_set_tx_pin(12);          // Sets pin D12 as the TX pin
  vw_set_ptt_inverted(true);  // Required for DR3100
  vw_setup(4000);         // Bits per sec

}


void loop(){

  //read the analog values from the accelerometer
  int xRead = analogRead(xPin);
  int yRead = analogRead(yPin);
  int zRead = analogRead(zPin);

  //convert read values to degrees -90 to 90 - Needed for atan2
  int xAng = map(xRead, minVal, maxVal, -90, 90);
  int yAng = map(yRead, minVal, maxVal, -90, 90);
  int zAng = map(zRead, minVal, maxVal, -90, 90);

  //Caculate 360deg values like so: atan2(-yAng, -zAng)
  //atan2 outputs the value of -? to ? (radians)
  //We are then converting the radians to degrees
  x = RAD_TO_DEG * (atan2(-yAng, -zAng) + PI);
  y = RAD_TO_DEG * (atan2(-xAng, -zAng) + PI);
  z = RAD_TO_DEG * (atan2(-yAng, -xAng) + PI);



  //Output the caculations
  Serial.print("x: ");
  Serial.print(x);
  Serial.print(" | y: ");
  Serial.print(y);
  Serial.print(" | z: ");
  Serial.println(z);
 

if(x<50&&x>20&&y<360&&y>0&&z<150&&z>40)
{
Serial.println("fw");
    const char *msg = "f";   // Message to be sent
    digitalWrite(13, true);      // Flash a light to show transmitting
    vw_send((uint8_t *)msg, strlen(msg)); //Sending the message
    vw_wait_tx(); // Wait until the whole message is gone
    Serial.println(*msg);
    Serial.println("transmitted");
    digitalWrite(13, false);   // Turn the LED off.
    delay(200);                 // A short gap
}
else if(x>=0&&x<=360&&y>50&&y<=360&&z>130&&z<210)
{
Serial.println("left");
    const char *msg = "l";   // Message to be sent
    digitalWrite(13, true);      // Flash a light to show transmitting
    vw_send((uint8_t *)msg, strlen(msg)); //Sending the message
    vw_wait_tx(); // Wait until the whole message is gone
    Serial.println(*msg);
    Serial.println("transmitted");
    digitalWrite(13, false);   // Turn the LED off.
    delay(200);                 // A short gap.


}
else if(x>0&&x<360&&y>15&&y<340&&z<20||z>345)
  {
    Serial.println("right"); //right
    const char *msg = "r";   // Message to be sent
    digitalWrite(13, true);      // Flash a light to show transmitting
    vw_send((uint8_t *)msg, strlen(msg)); //Sending the message
    vw_wait_tx(); // Wait until the whole message is gone
    Serial.println(*msg);
    Serial.println("transmitted");
    digitalWrite(13, false);   // Turn the LED off.
    delay(200);                 // A short gap.

  }
else
{
Serial.println("s"); //stop
    const char *msg = "s";   // Message to be sent
    digitalWrite(13, true);      // Flash a light to show transmitting
    vw_send((uint8_t *)msg, strlen(msg)); //Sending the message
    vw_wait_tx(); // Wait until the whole message is gone
    Serial.println(*msg);
    Serial.println("transmitted");
    digitalWrite(13, false);   // Turn the LED off.
    delay(200);                 // A short gap.
  
}
//}
delay(3000);

//just here to slow down the serial output - Easier to read
}
