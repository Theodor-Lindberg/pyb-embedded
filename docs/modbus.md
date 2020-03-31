# Modbus RTU communication
This document describes all the supported modbus functionality, parameters, hardware setup and examples to get up and running.

## Table Of Contents
1. [Hardware Setup](#1-Hardware-Setup)
2. [Supported Settings](#2-Supported-Settings)  
3. [Parameters](#3-Parameters)  
	3.1 [Discrete Output Coils](#3.1-Discrete-Output-Coils)  
	3.2 [Discrete Input Contacts](#3.2-Discrete-Input-Contacts)  
	3.3 [Analog Output Holding Registers](#3.3-Analog-Output-Holding-Registers)  
	3.4 [Analog Input Registers](#3.4-Analog-Input-Registers)
4. [Examples](#4-Examples)  
	4.1 [Modpoll](#4.1-Modpoll)

## 1. Hardware Setup

## 2. Supported Settings

## 3. Parameters

### 3.1 Discrete Outputs Coils
| Adress (hex) | Short name       | Description                                 | Default value |  
| -----------  | :---------------:| :------------------------------------------:| :------------:|  
| 0x0000       | BLUE_BOARD_LED   | Turn the blue LED on the board on or off.   | `0`           |  
| 0x0001       | GREEN_BOARD_LED  | Turn the green LED on the board on or off.  | `0`           |  
| 0x0002       | YELLOW_BOARD_LED | Turn the yellow LED on the board on or off. | `0`           |  
| 0x0003       | RED_BOARD_LED    | Turn the red LED on the board on or off.    | `0`           |  

### 3.2 Discrete Input Contacts
| Adress (hex) | Short name       | Description                                    |    
| -----------  | :---------------:| :---------------------------------------------:|   
| 0x0000       | BLUE_BOARD_LED   | Get the status of the blue LED on the board.   |    
| 0x0001       | GREEN_BOARD_LED  | Get the status of the green LED on the board.  |   
| 0x0002       | YELLOW_BOARD_LED | Get the status of the yellow LED on the board. |    
| 0x0003       | RED_BOARD_LED    | Get the status of the red LED on the board.    |  

### 3.3 Analog Output Holding Registers

### 3.4 Analog Input Registers