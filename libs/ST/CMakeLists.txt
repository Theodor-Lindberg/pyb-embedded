# Oscillator values in Hz
set(HSE_VALUE HSE_VALUE=12000000)
set(LSE_VALUE LSE_VALUE=32768)
set(EXTERNAL_CLOCK_VALUE EXTERNAL_CLOCK_VALUE=12288000)

# Oscillator timeouts in ms
set(HSE_STARTUP_TIMEOUT HSE_STARTUP_TIMEOUT=100)
set(LSE_STARTUP_TIMEOUT LSE_STARTUP_TIMEOUT=5000)

set(OSCILLATOR_SETTINGS ${HSE_VALUE}
                        ${HSE_STARTUP_TIMEOUT}
                        ${LSE_VALUE}
                        ${LSE_STARTUP_TIMEOUT}
                        ${EXTERNAL_CLOCK_VALUE})

add_subdirectory(system)
add_subdirectory(hal)