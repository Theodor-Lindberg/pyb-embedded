#include "BoardLEDs.hpp"
#include "DigitalOut.hpp"
#include "HwInitialize.hpp"
#include "mb_slave.hpp"

volatile uint32_t Timing_DelayMS; // Timing delay in millseconds.

extern "C" void SysTick_Handler(void) {
	if (Timing_DelayMS > 0) {
		Timing_DelayMS--;
	}
}

/* Private function prototypes -----------------------------------------------*/

void SystemClock_Config();
void DelayMS(volatile uint32_t time);

int main() {
	HwInitialize();
	ModbusSlave mb(SerialDriver::get_instance(DRIVER_PORT::USART_6), 130, BAUDRATE::RATE_9600, STOPBITS::SB_1, PARITY::NONE);
	mb.open();

	while(1) {
	}
}

/**
 * @brief Busy wait for a certain time.
 * 
 * @param uint32_t The time to wait in milliseconds.
 */
void DelayMS(volatile uint32_t ms_delay) {
	Timing_DelayMS = ms_delay;
	while(Timing_DelayMS != 0);
}