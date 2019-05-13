#!/usr/bin/env python
import serial
import sys
import queue
import threading

q= queue.Queue(999)

def serial_read(s):
    s.baudrate = 115200
    while True:
        line = s.readline()
        q.put(f"{s.name}: {line}")

port1 = sys.argv[1]
port2 = sys.argv[2]
print(f"using {port1} and {port2}")

s1 = serial.Serial(port1)
s2 = serial.Serial(port2)

thread1 = threading.Thread(target=serial_read, args=(s1,),).start()
thread2 = threading.Thread(target=serial_read, args=(s2,),).start()

while True:
    try:
        line = q.get(True, 1)
        print(line)
    except queue.Empty:
        pass
