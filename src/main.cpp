#include "BoardLEDs.hpp"
#include "BoardButton.hpp"
#include "SEGGER_RTT.h"
#include "USART_Driver.hpp"
#include "stm32f4xx_ll_bus.h"
 
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

int main()
{
	SerialDriver serial = SerialDriver::get_instance(DRIVER_PORT::USART_1);
	serial.close();
	serial.initialize(BAUDRATE::RATE_9600, DIRECTION::RX_TX, DATAWIDTH::B8, PARITY::NONE, 
						HWCONTROL::NONE, OVERSAMPLING::B8);
	

	// Enable the GPIO clock for port A and B
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
	RCC->APB2ENR |= RCC_APB2ENR_USART6EN;

	/*Board::get_board_led(Board::LED::BLUE).write(false);
	Board::get_board_led(Board::LED::GREEN).write(false);
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

	serial.open();

	while(1) {
		if (user_button.is_pressed() && !pressed) {
			pressed = true;
			serial.write(0x06U);
			//SEGGER_RTT_printf(0, "The button was pressed!\n\n");
		}
		else if (!user_button.is_pressed()) {
			pressed = false;
		}
	}
}