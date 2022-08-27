from socket import socket
from flask import Flask, render_template
from flask_socketio import SocketIO
import serial
import time
# Flask Set up
app = Flask(__name__)
app.config['SECRET_KEY']= "bruh"
socket = SocketIO(app)

# Serial Setup
ser = serial.Serial('COM3', baudrate = 9600, timeout=1)

# Serial returning
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
        print(removeSpace)
        print("loading...")
   socket.send(finalResult)

# Main page
@app.route("/")
def main():
    return render_template("index.html")

# Socketio Sending Message
@socket.on('message')
def handleMsg(msg):
    returnSerial()

# Start Flask Server w/ Socketio
if __name__ == "__main__":
    socket.run(app)
