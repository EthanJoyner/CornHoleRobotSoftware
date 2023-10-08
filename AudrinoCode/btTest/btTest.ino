#include <SoftwareSerial.h>
SoftwareSerial btSerial(10, 11); // RX, TX
char Incoming_value = 0;
                
void setup() 
{
  Serial.begin(9600);         
  pinMode(13, OUTPUT); 
}

void loop(){
  if(btSerial.available() > 0)  
  {
    Incoming_value = btSerial.read();      
    btSerial.println(Incoming_value);        
       
    if(Incoming_value == '1')             
      digitalWrite(13, HIGH);  
    else if(Incoming_value == '0')       
      digitalWrite(13, LOW);   
  }                            
} 
