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

# # Serial returning
def returnSerial():
#    print("Step 1: read in Serial from ADR") 
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
#    print("Step 2: Finish formatting in array and send to JS via ws")

# Main page
@app.route("/")
def main():
    return render_template("index.html")

@app.route("/ctrl")
def ctrl():
    return render_template("ctrl.html")

@app.route("/seq")
def seq():
    return render_template("seq.html")

@app.route("/admin")
def admin():
    return render_template("admin.html")

@app.route("/docs")
def docs():
    return render_template("doc.html")

@app.route("/elements")
def elements():
    return render_template("elements.html")

# Socketio Sending Message
@socket.on('message')
def handleMsg(msg):
    returnSerial()
    # print("Step 7: Sent controller code over serial")

    # When receiving a message from WS, take in convert it to bytes, and send it over serial 
    res = bytes(msg, 'utf-8')
    ser.write(res)

# Start Flask Server w/ Socketio
if __name__ == "__main__":
    socket.run(app, host= '0.0.0.0', port=5000)
