import minimalmodbus as mm

inst = mm.Instrument('COM4', 17)
inst.serial.baudrate = 9600
