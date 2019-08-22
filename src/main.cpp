#include "BoardLEDs.hpp"
#include "DigitalOut.hpp"
#include "HwInitialize.hpp"
#include "USART_Driver.hpp"

volatile uint32_t Timing_DelayMS; // Timing delay in millseconds.

extern "C" void SysTick_Handler(void) {
	if (Timing_DelayMS > 0) {
		Timing_DelayMS--;
	}
}

/* Private function prototypes -----------------------------------------------*/

void SystemClock_Config();
void DelayMS(volatile uint32_t time);

const char* const  message = "Hello\n";

int main() {
	HwInitialize();
	SerialDriver ser = SerialDriver::get_instance(DRIVER_PORT::USART_6);

	ser.open();

	while(1) {
		ser.print(reinterpret_cast<const uint8_t*>(message));
		DelayMS(1000U);
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