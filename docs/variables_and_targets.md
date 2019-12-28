# CMake Variables and Targets

## Variables
This project provides some CMake variables for use during configuration and other explicitly specified build targets.

| Variable           | Description     | Possible Values      | Default Value |
|--------------------|-----------------|----------------------|---------------|
| `CMAKE_BUILD_TYPE` | This etermines the build type of the application. | `Debug`/`Release`            | `Release`     |
| `CMAKE_TOOLCHAIN_FILE`| Determines which compiler should be used, a self supplied toolchain can be used but two configurations is included in the project. | `GCC.cmake`/`GNU-ARM-Toolchain.cmake`| `GNU-ARM-Toolchain.cmake`|
| `BUILD_TESTS`| An option used to determine if the test executable should or should not be built.| `ON`/`OFF`| `OFF`|
| `ENABLE_COVERAGE`| An option used to determine whether test coverage should be enabled or not.| `ON`/`OFF`| `OFF`|
| `GEN_DOCS`| An option used to determine if documentation will or will not be generated. | `ON`/`OFF`| `ON`|

## Targets
| Target           | Description                                                       |
|------------------|-------------------------------------------------------------------|
| `[Nothing]`      | Build the application (including the tests if `BUILD_TESTS=ON`).  |
