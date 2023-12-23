void doSeq(String seqCode){
  //Do something with the data - like print it
      Serial.print("Code: ");
      Serial.println(seqCode);

      signalType = seqCode.substring(0, 1).toInt();
      moveType = seqCode.substring(1, 2).toInt();
      moveTime = seqCode.substring(2, 6).toInt();


      switch (moveType) {
        // Move forward
        case 1:
          //            Serial.println("Move Forward");
          break;

        // Move backward
        case 2:
          //            Serial.println("Move Backwards");
          break;

        // Turn left
        case 3:
          //            Serial.println("Turn Left");
          break;

        // Turn right
        case 4:
          //            Serial.println("Turn Right");
          break;

        // Arm up
        case 5:
          //            Serial.println("Arm Up");
          break;

        // Arm down
        case 6:
          //            Serial.println("Arm Down");
          break;

          // Compress to
        case 7:
          //            Serial.println("compress to");
          break;

        // Default
        default:
          //            Serial.println("Invalid Movement Code");
          break;
      }
}