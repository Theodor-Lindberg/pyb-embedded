#pragma once

enum class DRIVER_PORT;

/**
 * @brief Initialize all hardware required for the application.
 */
void HwInitialize();

/**
 * @brief Configure the system clock to use HSE and PLL.
 *      The system Clock is configured as follow:
 *      System Clock source            = PLL (HSE)
 *      SYSCLK(Hz)                     = 168000000
 *      HCLK(Hz)                       = 168000000
 *      AHB Prescaler                  = 1
 *      APB1 Prescaler                 = 4
 *      APB2 Prescaler                 = 2
 *      HSE Frequency(Hz)              = 12000000
 *      PLL_M                          = 12
 *      PLL_N                          = 336
 *      PLL_P                          = 2
 *      VDD(V)                         = 3.3
 *      Main regulator output voltage  = Scale1 mode
 *      Flash Latency(WS)              = 5
 */
void SystemClock_Config();

/**
 * @brief Initialize the System Timer, configure 1 millisecond interrupt and start the timer.  
 */
void SystemTick_Config();

/**
 * @brief Configure the pins
 * 
 * @param driver_port The UART or USART port.
 */
void UsartPins_Config(DRIVER_PORT driver_port);

