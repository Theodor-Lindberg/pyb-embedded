#include "BoardLEDs.hpp"
#include "BoardButton.hpp"
#include "SEGGER_RTT.h"
#include "USART_Driver.hpp"
#include "stm32f4xx_ll_system.h"
#include "stm32f4xx_ll_rcc.h"
 
extern "C" void EXTI3_IRQHandler(void) {
	if (EXTI->PR & EXTI_PR_PR3) {
		// Clear interrupt flag
		EXTI->PR |= EXTI_PR_PR3;
		// Disable other interrupts
		NVIC_DisableIRQ(EXTI3_IRQn);

		Board::get_board_led(Board::LED::BLUE).toggle();

		// Enable interrupts again
		NVIC_EnableIRQ(EXTI3_IRQn);
	}
}

/* Private function prototypes -----------------------------------------------*/

void SystemClock_Config();

int main()
{
	SystemClock_Config();
	/*SerialDriver serial = SerialDriver::get_instance(DRIVER_PORT::USART_1);
	serial.close();
	serial.initialize(BAUDRATE::RATE_9600, DIRECTION::RX_TX, DATAWIDTH::B8, PARITY::NONE, 
						HWCONTROL::NONE, OVERSAMPLING::B8);*/
	

	// Enable the GPIO clock for port A and B
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

	/*RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
	RCC->APB2ENR |= RCC_APB2ENR_USART6EN;*/

	Board::get_board_led(Board::LED::BLUE).write(false);
	/*Board::get_board_led(Board::LED::GREEN).write(false);
	Board::get_board_led(Board::LED::YELLOW).write(false);
	Board::get_board_led(Board::LED::RED).write(false);*/

	// Enable the System Configuration Controller clock
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

	// Enable interrupt line for port B3
	SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI3_PB;

	// Interuppt line is not masked
	EXTI->IMR = EXTI_IMR_IM3;

	// Trigger on falling edge
	EXTI->FTSR |= EXTI_FTSR_TR3;

	NVIC_SetPriority(EXTI3_IRQn, 0);
	NVIC_EnableIRQ(EXTI3_IRQn);
	Button user_button = Board::get_board_button();
	bool pressed = false;

	//serial.open();

	while(1) {
		Board::get_board_led(Board::LED::BLUE).toggle();
	}
}

/**
 * @brief Configure the system clock to use HSE and PLL.
 *      The system Clock is configured as follow :
 *		System Clock source            = PLL (HSE)
 *      SYSCLK(Hz)                     = 168000000
 *      HCLK(Hz)                       = 168000000
 *      AHB Prescaler                  = 1
 *      APB1 Prescaler                 = 4
 *      APB2 Prescaler                 = 2
 *      HSE Frequency(Hz)              = 12000000
 *      PLL_M                          = 12
 *      PLL_N                          = 336
 *      PLL_P                          = 4
 *      VDD(V)                         = 3.3
 *      Main regulator output voltage  = Scale1 mode
 *      Flash Latency(WS)              = 5
 */
void SystemClock_Config() {
  LL_RCC_HSE_Enable();
  while(LL_RCC_HSE_IsReady() != 1)
  {
  };

  LL_FLASH_SetLatency(LL_FLASH_LATENCY_5);

  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_12, 336U, LL_RCC_PLLP_DIV_4);
  LL_RCC_PLL_Enable();
  while(LL_RCC_PLL_IsReady() != 1)
  {
  };

  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
  {
  };

  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_4);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_2);

  SystemCoreClockUpdate();
}