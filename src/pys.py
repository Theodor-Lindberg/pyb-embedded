import serial

ser = serial.Serial()
ser.baudrate = 9600
ser.port = "COM10"
ser.parity = serial.PARITY_NONE
ser.stopbits = serial.STOPBITS_ONE
ser.bytesize = serial.EIGHTBITS
ser.timeout = 1