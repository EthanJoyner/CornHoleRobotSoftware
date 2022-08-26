# from flask import Flask
# from flask_socketio import SocketIO, send
import serial
import time

ser = serial.Serial('COM3', baudrate = 9600, timeout=1)

while 1:
   arduinoData = ser.readline().decode('Ascii')
   print(arduinoData)

# app = Flask(__name__)
# app.config['SECRET_KEY'] = 'secret!'
# socketio = SocketIO(app)

# if __name__ == '__main__':
#     socketio.run(app)

# @socketio.on('message')
# def handle_message(message):
#     send(message)

# @socketio.on('json')
# def handle_json(json):
#     send(json, json=True)

# @socketio.on('my event')
# def handle_my_custom_event(json):
#     emit('my response', json)

