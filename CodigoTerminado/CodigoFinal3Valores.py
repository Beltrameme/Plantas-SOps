import serial
import time
import matplotlib.pyplot as plt
import numpy as np
ser = serial.Serial( #configuraciones para leer el peurto serie de la rasp
    port='COM14',\
    baudrate=9600,\
    parity=serial.PARITY_NONE,\
    stopbits=serial.STOPBITS_TWO,\
    bytesize=serial.EIGHTBITS,\
        timeout=0)

print("connected to: " + ser.portstr)
count=0
luz = []
temp = []
humedad = []

valor = ser.read(10)
while True:
    for line in ser.read(10):
        if count > 2:
            count = 1
        else:
            count = count + 1
        if count == 1:  # ya que los valores vienen en un orden determinado pero sin saber cual, hago un pequeño switch para ubicarlos correctamente
            temp.append(int(line))
        if count == 2:
            humedad.append(int(line))
        if count == 3:
            luz.append(int(line))

    plt.plot(temp,'r', humedad,'b',luz,'g') #uso matplotlib para graficar los 3 valores en el mismo grafico
    plt.draw()
    plt.pause(0.05)
plt.show(block = True)
ser.close()