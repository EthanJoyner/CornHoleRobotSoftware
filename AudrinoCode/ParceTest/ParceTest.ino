// Controller Variables
int signalType;
int analogLeft;
int analogRight;
int armUp;
int armDown;
int fire1;
int fire2;

//Seq Variables
int moveType;
int moveTime;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  while (Serial.available() > 0){
      
    String dataIn = Serial.readString();
  
  
    if (dataIn.substring(0,1).toInt() == 1){
  
      signalType = dataIn.substring(0,1).toInt();
      analogLeft = dataIn.substring(1,3).toInt();
      analogRight = dataIn.substring(3,5).toInt();
      armUp = dataIn.substring(5,6).toInt();
      armDown = dataIn.substring(6,7).toInt();
      fire1 = dataIn.substring(7,8).toInt();
      fire2 = dataIn.substring(8,9).toInt();
    
     //Do something with the data - like print it
      Serial.print("Code: ");
      Serial.println(dataIn);
    
      Serial.print("Type: ");
      Serial.println(signalType);
      
      Serial.print("AL: ");
      Serial.println(analogLeft);
      
      Serial.print("AR: ");
      Serial.println(analogRight);
      
      Serial.print("AU: ");
      Serial.println(armUp);
      
      Serial.print("AD: ");
      Serial.println(armDown);
      
      Serial.print("Fire1: ");
      Serial.println(fire1);
      
      Serial.print("Fire2: ");
      Serial.println(fire2); 
      
      } else if (dataIn.substring(0,1).toInt() == 2){
  
        //Do something with the data - like print it
        Serial.print("Code: ");
        Serial.println(dataIn);
          
        signalType = dataIn.substring(0,1).toInt();
        moveType = dataIn.substring(1,2).toInt();
        moveTime = dataIn.substring(2,6).toInt();
  
        Serial.print("Type: ");
        Serial.println(signalType); 
  
        Serial.print("Movetype: ");
        Serial.println(moveType); 
  
        switch (moveType){
          // Move forward
          case 1:
            Serial.println("Move Forward"); 
            break;
            
          // Move backward
          case 2:
            Serial.println("Move Backwards");
            break; 
          
          // Turn left
          case 3:
            Serial.println("Turn Left"); 
            break;
          
          // Turn right
          case 4:
            Serial.println("Turn Right");
            break; 
          
          // Arm up
          case 5:
            Serial.println("Arm Up");
            break; 
          
          // Arm down
          case 6:
            Serial.println("Arm Down");
            break;
            
          // Default
          default:
            Serial.println("Invalid Movement Code");
            break;
          }
        
        Serial.print("Time: ");
        Serial.println(moveTime); 
       
        
        } else {
          Serial.println("No Signal...");
          //Do something with the data - like print it
          Serial.print("Code: ");
          Serial.println(dataIn);
          
          }
  
  }
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(analogLeft);                       // wait for a second
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    delay(analogLeft);                       // wait for a second
}
