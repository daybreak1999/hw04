from abc import abstractclassmethod
import serial
import sys

if len(sys.argv) < 1:
    print ("No port input")
s = serial.Serial(sys.argv[1])

a = "/park/run " + sys.argv[2] +" " + sys.argv[3] + " " + sys.argv[4] + " \n"
print (a)
s.write(a.encode())