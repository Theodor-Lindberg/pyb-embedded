#include "HwInitialize.hpp"
#include "USART_Driver.hpp"
#include "stm32f4xx_ll_system.h"
#include "stm32f4xx_ll_rcc.h"
#include "stm32f4xx_ll_gpio.h"

void HwInitialize() {
	SystemClock_Config();
	SystemTick_Config();
	UsartPins_Config(DRIVER_PORT::USART_6);
}

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

void SystemTick_Config() {
	if (SysTick_Config(SystemCoreClock / 1000U)) { // Trigger interrupt every millisecond
		while (true);
	}
}

void UsartPins_Config(DRIVER_PORT driver_port) { 
	switch(driver_port) {
		case DRIVER_PORT::USART_1:
			break;
		case DRIVER_PORT::USART_2:
			break;
		case DRIVER_PORT::USART_3:
			break;
		case DRIVER_PORT::UART_4:
			break;
		case DRIVER_PORT::UART_5:
			break;
		case DRIVER_PORT::USART_6:
			RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;  // Initialize GPIOC bus
			RCC->APB2ENR |= RCC_APB2ENR_USART6EN;

			// TX pin
			LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_6, LL_GPIO_MODE_ALTERNATE);
			LL_GPIO_SetAFPin_0_7(GPIOC, LL_GPIO_PIN_6, LL_GPIO_AF_8);
			LL_GPIO_SetPinSpeed(GPIOC, LL_GPIO_PIN_6, LL_GPIO_SPEED_FREQ_HIGH);
			LL_GPIO_SetPinOutputType(GPIOC, LL_GPIO_PIN_6, LL_GPIO_OUTPUT_PUSHPULL);
			LL_GPIO_SetPinPull(GPIOC, LL_GPIO_PIN_6, LL_GPIO_PULL_UP);

			// RX pin
			LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_7, LL_GPIO_MODE_ALTERNATE);
			LL_GPIO_SetAFPin_0_7(GPIOC, LL_GPIO_PIN_7, LL_GPIO_AF_8);
			LL_GPIO_SetPinSpeed(GPIOC, LL_GPIO_PIN_7, LL_GPIO_SPEED_FREQ_HIGH);
			LL_GPIO_SetPinOutputType(GPIOC, LL_GPIO_PIN_7, LL_GPIO_OUTPUT_PUSHPULL);
			LL_GPIO_SetPinPull(GPIOC, LL_GPIO_PIN_7, LL_GPIO_PULL_UP);
			break;
		default:
			 __builtin_unreachable();
			 break;
	}
}