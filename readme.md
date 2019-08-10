[![Build Status](https://travis-ci.org/Theodor-Lindberg/pyb-embedded.svg?branch=master)](https://travis-ci.org/Theodor-Lindberg/pyb-embedded)

## Table of contents  
1. [About](#1-About)
2. [Configuring And Building The Project](#2-Configuring-And-Building-The-Project)  
    2.1 [Command Line With Unix Makefiles](#2.1-Command-Line-With-Unix-Makefiles)  
    2.2 [Visual Studio Code With Unix Makefiles](#2.2-Visual-Studio-Code-With-Unix-Makefiles)
3. [Flashing And Debugging](#3-Flashing-And-Debugging)  
    3.1 [Hardware Setup For SWD](#3.1-Hardware-Setup-For-SWD)  
    3.2 [Software Setup](#3.2-Software-Setup)  
    3.3 [Flashing Using J-Link Commander](#3.3-Flashing-Using-J-Link-Commander)  
    3.4 [Debugging from Visual Studio Code](#3.4-Debugging-from-Visual-Studio-Code)
4. [Software Revisions](#4-Software-Revisions)  
  
## 1 About  
I have not yet decided what the code should do, but the philosophy of the project is to be stable, scalable with good test coverage, continuous integration, documentation and be as independent as possible from operating systems, editors and build tools.
  
## 2 Configuring And Building The Project
The project uses CMake so many different build systems can be targeted but I personally use Unix Makefiles from Visual Studio Code. The build variants are *App* and *Tests*, each with Debug and Release. *App* is the main project and should be built with the *GCC 7.3.1 Cortex M4* kit, *Tests* builds the unit tests to run on the desktop. To get the best intellisense and syntax highlighting choose the *ARM* configuration when developing for target and the *Desktop* configuration otherwise.

### 2.1 Command Line With Unix Makefiles  
To build from the command line write the following from the repository root.  
For a release build write:  
```  
mkdir build
cd build && cmake -G "Unix Makefiles" -D "CMAKE_TOOLCHAIN_FILE=../CMake/GNU-ARM-Toolchain.cmake" ../  
make  
```
or for a debug build write:  
```  
mkdir build
cd build && cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug -D "CMAKE_TOOLCHAIN_FILE=../CMake/GNU-ARM-Toolchain.cmake" ../  
make  
```  

### 2.2 Visual Studio Code With Unix Makefiles  
To build from Visual Studio Code the [CMake Tools-extension][cmake-tools] must be installed. If you don't have CMake in your *path* variable you can specify the `cmake.cmakePath` in the *settings.json* file. You can then select build variant and kit from the blue menu bar at the bottom in Visual Studio Code.  

## 3 Flashing And Debugging  
Flashing and debugging can be done using many different tools but I will only explain two different tools. 

### 3.1 Hardware Setup For SWD  
I use the same pins on the board as suggested in the [micropython wiki][micropython-wiki] and the *Segger JLink Edu Mini* with the *SWD Cable Breakout Board* from *Adafruit*.  
```
Segger JLink Edu Mini | Adafruit SWD Cable Breakout Board | pyboard v1.1
--------------------- | --------------------------------- | ---------------
PIN1    (VTref)        -> (Vref)                           -> 3V3
PIN2    (SWDIO/TMS)    -> (SWIO)                           -> PA13 (X21-2)
PIN3    (GND)          -> (GND)                            -> GND
PIN4    (SWDCLK/TCK)   -> (CLK)                            -> PA14 (X20-2)
PIN5    (GND)          -> (GND)
PIN6    (SWO/TDO)      -> (SWO)
PIN7    (---)          -> (KEY
PIN8    (TDI)          -> (NC)
PIN9    (NC)           -> (GNDd)
PIN10   (nReset)       -> (nReset)                         -> RST
```  
Since the leds on the board conflicts with the programming over SWD you should always make the following connection to be sure the programming is successful.
```
pyboard v1.1 | pyboard v1.1
-------------| -------------------
3V3           -> BOOT0 (P1/DFU)
```  
### 3.2 Software Setup 
The *Segger J-Link Software* must be installed and can be downloaded from [here][segger-download].

### 3.3 Flashing using J-Link Commander  
1. Connect a jumper cable between 3v3 and BOOT0 on the board.
2. Add power to the board.
3. Connect the j-link to the board and plug it into the computer.
4. Start *J-Link Commander*, it should detect the j-link automatically.
5. To connect to the board write `connect`.
6. Specify `STM32F405RG` as the target device.
7. Write `S` to connect over SWD.
8. Choose the default target interface speed (*4000 kHz*).
9. To flash a hex write `loadfile <path to file>`.
10. You are now done so you can quit the program by writing `exit`.
11. Remove the temporary jumper between 3V3 and BOOT0.
12. Reset the board by either cycling the power or pressing the reset button.  
You are now done and your program should be running.  

### 3.4 Debugging from Visual Studio Code  
To flash and debug from Visual Studio Code the [Cortex Debug-extension][cortex-debug] must be installed. If you don't have the J-Link software in your path variable you can specify it using the `cortex-debug.JLinkGDBServerPath` in the *setting.json* file, note that it has to be the full path to your *JLinkGDBServerCL*.

## 4 Software Revisions  
This is a list of all the softwares and their versions that I currently use:  
* Visual Studio Code *1.37.0*  
    * C/C++ *0.24.1*  
    * CMake *0.0.17*
    * Cmake Tools *1.1.3*
    * Cortex Debug *0.3.1*
    * Catch2 and Google Test Explorer *2.6.6*
    * Better Comments *2.0.5*
    * Doxygen Documentation Generator *0.5.0*
* CMake *3.12.18081601-MSVC_2*
* GNU Make *3.81*
* GNU ARM Embedded Toolchain *7.3.1*  
* Segger JLink *4.66c*  
* Segger JLink EDU Mini, Firmware: *compiled Mar 15 2019 12:47:02*, Hardware: *1.00*
* CMSIS *5-5.5.1*
* ST Low Level library *1.24.0*
* Catch2 *2.9.1*

[micropython-wiki]:https://github.com/micropython/micropython/wiki/Programming-Debugging-the-pyboard-using-ST-Link-v2#Hardware-Setup  
[segger-download]:https://www.segger.com/downloads/jlink/#J-LinkSoftwareAndDocumentationPack
[cortex-debug]:https://marketplace.visualstudio.com/items?itemName=marus25.cortex-debug
[cmake-tools]:https://marketplace.visualstudio.com/items?itemName=vector-of-bool.cmake-tools
[build_status]:https://travis-ci.org/Theodor-Lindberg/pyb-embedded.svg?branch=master