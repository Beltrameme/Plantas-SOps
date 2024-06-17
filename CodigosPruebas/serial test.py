import serial
import time
import matplotlib.pyplot as plt
import numpy as np
start = time.time()
ser = serial.Serial(
    port='COM3',\
    baudrate=9600,\
    parity=serial.PARITY_NONE,\
    stopbits=serial.STOPBITS_TWO,\
    bytesize=serial.EIGHTBITS,\
        timeout=0)

print("connected to: " + ser.portstr)
count=1
valor = []
tiempo = []
while True:
    for line in ser.read(10):
        time.sleep(0.5)
        print(count, int(line))
        count = count+1
        valor.append(int(line))
        tiempo.append((time.time()-start))

    plt.plot(tiempo,'r', valor,'g')
    plt.draw()
    plt.pause(0.05)
plt.show(block = True)

ser.close()