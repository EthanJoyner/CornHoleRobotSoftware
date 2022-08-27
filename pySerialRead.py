import serial
import time

ser = serial.Serial('COM3', baudrate = 9600, timeout=1)

def returnSerial():
   finalResult = []
   arduinoData = ser.readline().decode('Ascii')
   dirtyArrayFormat = ((arduinoData).split(','))

   for i in dirtyArrayFormat:
      removeSpace = i.strip()
      try:
         intoNum = float(removeSpace)
         finalResult.append(intoNum)
      except:
         print("...")
   print(finalResult)

while 1:
   returnSerial()
 



