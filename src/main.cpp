#include "stm32f4xx_ll_system.h"
#include "stm32f4xx_ll_rcc.h"
#include "BoardLEDs.hpp"
#include "DigitalOut.hpp"

GPIO_DEF_DECLARATION

__IO uint32_t Timing_DelayMS; // Timing delay in millseconds.

extern "C" void SysTick_Handler(void) {
	if (Timing_DelayMS > 0) {
		Timing_DelayMS--;
	}
}

/* Private function prototypes -----------------------------------------------*/

void SystemClock_Config();
void DelayMS(__IO uint32_t time);

int main()
{
	SystemClock_Config();
	if (SysTick_Config(SystemCoreClock / 1000U)) { // Trigger interrupt every millisecond
		while (true);
	}

	// Enable the GPIO clock for port B
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

	while(1) {
		Board::get_board_led(Board::LED::BLUE).toggle();
		DelayMS(500U);
	}
}

/**
 * @brief Configure the system clock to use HSE and PLL.
 *      The system Clock is configured as follow:
 *		System Clock source            = PLL (HSE)
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
void SystemClock_Config() {
  LL_RCC_HSE_Enable();
  while(LL_RCC_HSE_IsReady() != 1);

  LL_FLASH_SetLatency(LL_FLASH_LATENCY_5);

  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_12, 336U, LL_RCC_PLLP_DIV_2);
  LL_RCC_PLL_Enable();
  while(LL_RCC_PLL_IsReady() != 1);

  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL);

  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_4);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_2);

  SystemCoreClockUpdate();
}

/**
 * @brief Busy wait for a certain time.
 * 
 * @param uint32_t The time to wait in milliseconds.
 */
void DelayMS(__IO uint32_t ms_delay)
{
  Timing_DelayMS = ms_delay;
  while(Timing_DelayMS != 0);
}