from flask import Flask, render_template, redirect, request, url_for
import serial
import sys
import struct

app = Flask(__name__)

RESET = 1
PORT = "/dev/ttyUSB1"

print("Connecting to :" + PORT)
ser = serial.Serial(PORT, baudrate = 9600, timeout=1)

@app.route("/")
def index():
        return render_template('index.html')

@app.route("/reset")
def reset():
	ser.write(struct.pack('>B', RESET))
	return redirect(url_for('index'))
