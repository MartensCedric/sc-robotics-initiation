from flask import Flask, render_template, redirect, request, url_for
import serial
import sys

app = Flask(__name__)

RESET = 1

port = "/dev/ttyUSB1"
print("Connecting to :" + port)
ser = serial.Serial(port,baudrate = 9600, timeout=1)

@app.route("/")
def index():
        return render_template('index.html')

@app.route("/reset")
def reset():
	ser.write(bytes([RESET]))
	return redirect(url_for('index'))
