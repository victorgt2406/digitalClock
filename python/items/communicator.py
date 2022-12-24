# Importing Libraries
import serial
import time

class Communicator:
    def __init__(self) -> None:
        self.arduino = serial.Serial(port='COM3', baudrate=115200, timeout=.1)
    def write_read(self,x):
        self.arduino.write(bytes(x, 'utf-8'))
        time.sleep(0.025)
        data = self.arduino.readline()
        time.sleep(0.025)
        return data

    def close(self):
        self.arduino.close()

    def open(self):
        self.arduino.open()
        time.sleep(1)


    def isOpen(self):
        return self.arduino.isOpen()
