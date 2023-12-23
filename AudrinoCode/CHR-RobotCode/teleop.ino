void doTeleop(String teleopCode){
      signalType = teleopCode.substring(0, 1).toInt();
      analogLeft = teleopCode.substring(1, 3).toInt();
      analogRight = teleopCode.substring(3, 5).toInt();
      armUp = teleopCode.substring(5, 6).toInt();
      armDown = teleopCode.substring(6, 7).toInt();
      playerFireReady = teleopCode.substring(7, 8).toInt();

      if (teleopCode.substring(8, 11) == "und") {
        targetPSI = 0;
      } else {
        targetPSI = teleopCode.substring(8, 11).toInt();
      }
}