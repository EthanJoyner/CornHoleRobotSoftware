void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
String testWord = "938373";

int wordLength = testWord.length();

for(int i=0; i<wordLength; i++){
  Serial.println(testWord[i]);
}

Serial.println(testWord);

String firstTwo = (String)testWord[0] + (String)testWord[1];
Serial.println(firstTwo);

int intFirstTwo = firstTwo.toInt();

Serial.println(intFirstTwo+2);

}


void loop() {
  // put your main code here, to run repeatedly:

}
