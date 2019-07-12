from flask import Flask, render_template, redirect, request, url_for, jsonify, make_response
import serial
import sys
import struct

import threading, Queue

app = Flask(__name__)

RESET = 1
PORT = "/dev/ttyUSB2"

currentNumber = struct.pack('>B', 0)
reading = True

print("Connecting to :" + PORT)
ser = serial.Serial(PORT, baudrate = 9600, timeout=2)

def read_serial():
    global currentNumber
    while reading:
        try:
            currentNumber = ser.read()
        except Exception as e: print(e)

thread = threading.Thread(target = read_serial)
thread.start()

@app.route("/")
def index():
        return render_template('index.html')

@app.route("/reset")
def reset():
	ser.write(struct.pack('>B', RESET))
        currentNumber = struct.pack('>B', 0)
	return redirect(url_for('index'))

@app.route("/time")
def time():
    unpacked = struct.unpack('>B', currentNumber)
    obj = jsonify(unpacked)
    return make_response(obj, 200)

@app.route("/stop")
def stop():
    global reading
    reading = False
    ser.close()
    print("Stopped thread")
