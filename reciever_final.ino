//Receiver code for head motion controlled wheelchair 

int trigpin=3;
int echopin=2;
float pintime;
float distance;
#include "VirtualWire.h"
byte message[VW_MAX_MESSAGE_LEN]; // a buffer to store the incoming messages
byte messageLength = VW_MAX_MESSAGE_LEN; // the size of the message
int count;
int i;
void setup()
{
    Serial.begin(9600);  // Debugging only
    //Serial.println("setup"); //Prints "Setup" to the serial monitor
    vw_set_rx_pin(12);       //Sets pin D0 as the RX Pin
    vw_set_ptt_inverted(true); // Required for DR3100
    vw_setup(4000);      // Bits per sec
    vw_rx_start();       // Start the receiver PLL running
    pinMode(trigpin,OUTPUT);//WE give VAlues to trig pin
    pinMode(echopin,INPUT);//we r reieving info from the echo pin
    pinMode(7, OUTPUT);
    pinMode(8, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(13, OUTPUT);
}

void loop()
{
digitalWrite(trigpin,LOW);
delayMicroseconds(2000);
digitalWrite(trigpin,HIGH);
delayMicroseconds(100);
digitalWrite(trigpin,LOW);
pintime=pulseIn(echopin,HIGH);//time taken for the pulse(high) to go from trig pin to echo pin in microseconds
distance=0.0129921*pintime/2;
distance=distance*0.0254;
Serial.println("The distance is:");
Serial.println(distance);


if(distance<=0.20)
{
Serial.println("Ultrasonic Stop");
   PORTH |= _BV(PH4);  
   PORTH &= ~_BV(PH5);
   PORTB |= _BV(PB7);
   PORTG &= ~_BV(PG5);
   analogWrite(9, 0);
   analogWrite(11, 0);
}

else
   {
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;
    if (vw_get_message(buf, &buflen)) // Non-blocking
    {
  int i;
     
  
  for (i = 0; i < buflen; i++)
  {
            
      if (buf[i]==0x73)
        {
          Serial.println("Stop");
          PORTH |= _BV(PH4);  
          PORTH &= ~_BV(PH5);
          PORTB |= _BV(PB7);
          PORTG &= ~_BV(PG5);
          analogWrite(9, 0);
          analogWrite(11, 0);
          
        }
    else
    {
        if (buf[i]==0x6C)
        {
          Serial.println("left");
          PORTH |= _BV(PH4);  
          PORTH &= ~_BV(PH5);
          PORTB |= _BV(PB7);
          PORTG &= ~_BV(PG5);
          analogWrite(9, 0);
          analogWrite(11, 255);   
          
        }
   if (buf[i]==0x66)
        {
          Serial.println("forward");
          PORTH |= _BV(PH4);  
          PORTH &= ~_BV(PH5);
          PORTB |= _BV(PB7);
          PORTG &= ~_BV(PG5);
            analogWrite(9, 255);
            analogWrite(11, 255);
         
            
        }
   if (buf[i]==0x72)
        {
          Serial.println("right");
          PORTH |= _BV(PH4);  
          PORTH &= ~_BV(PH5);
          PORTB |= _BV(PB7);
          PORTG &= ~_BV(PG5);
          analogWrite(9, 255);
          analogWrite(11, 0);
         
           
        }
   
             
    }
}
           
    
}
}
}
 








  
