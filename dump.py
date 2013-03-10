#!/usr/bin/python

import serial
import time
import sys

# Usage ./dump.py serial_device file_name
 
MEMORY_SIZE = 2**16

ser = serial.Serial(sys.argv[1], 9600, timeout=10)
file = open(sys.argv[2], "wb")
time.sleep(2)
i = 0
ser.write(chr(0xff))
while i < MEMORY_SIZE:
  byte_value = ser.read()
  file.write(byte_value)
  i = i + 1
file.close()
