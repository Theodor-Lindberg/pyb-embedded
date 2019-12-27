# Directory Structure

This is the directory structure that this project uses:  
```
	pyb-embedded/  
	├───.vscode  
	├───bin/  
	├───build/  
	├───cmake/  
	├───docs/  
	├───third_party/  
	│   ├───cmsis/  
	│   │   └───inc/  
	│   ├───SEGGER/  
	│   │   ├───RTT/  
	│   │   └───Syscalls/  
	│   └───ST/  
	│       ├───hal/  
	│       │   ├───inc/  
	│       │   └───src/  
	│       └───system/  
	│           ├───inc/  
	│           └───src/  
	├───linker/  
	├───src/  
	│   ├───hal/  
	│   │   ├───desktop/  
	│   │   └───target/  
	│   ├───modbus/  
	│   └───utilities/  
	└───tests/  
```
Here is a brief explanation of each one of them:

| Directory     | Purpose                                                             |
|---------------|---------------------------------------------------------------------|
| `.vscode`     | Contains configuration files for Visual Studio Code.                |
| `bin`         | This folder is generated upon compile time and contains the final binaries. |
| `build`       | Contains all the intermediate files during compilation and automatically generated. |
| `cmake`       | Contains the different toolchain configurations for compilers.      |
| `docs`        | Contains documentation for the project Doxygen configuration files. |
| `third_party` | Contains third party code.                                          |
| `third_party/cmsis` | Vendor independent abstraction layer for Arm Cortex microcontrollers.|
| `third_party/SEGGER` | Contains the implementation for Real-Time Transfer from SEGGER.|
| `third_party/ST/hal` | Contains a low-level abstraction layer for peripherals from ST.|
| `third_party/ST/system` | Abstraction layer and configuration files for the core.   |
| `linker`      | Contains the linker file for the compiler.                          |
| `src`         | Contains the source code for the application including headers.     |
| `src/hal`     | Contains a native and desktop ported hardware abstraction layer.    |
| `src/modbus`  | Contains the implementation for the Modbus protocol.                |
| `src/utilites`| Contains configuration files for Visual Studio Code. |
| `tests`       | Contains test files to unit test non third party code. |