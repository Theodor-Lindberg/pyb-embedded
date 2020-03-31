#include "BoardLEDs.hpp"
#include "DigitalOut.hpp"
#include "HwInitialize.hpp"
#include "ModbusSlave.hpp"
#include "BoardButton.hpp"

volatile uint32_t Timing_DelayMS; // Timing delay in millseconds.

extern "C" void SysTick_Handler(void) {
	if (Timing_DelayMS > 0) {
		Timing_DelayMS--;
	}
}

/* Private function prototypes -----------------------------------------------*/

void DelayMS(volatile uint32_t time);

int main() {
	HwInitialize();
	DigitalOut blue_led = board::get_board_led(board::LED::BLUE);
	blue_led.write(false);
	SerialDriver *serial = SerialDriver::get_instance(DRIVER_PORT::USART_6);
	ModbusSlave modbus_slave(serial, TIMER::TIMER14, 17, BAUDRATE::RATE_9600, STOPBITS::SB_1, PARITY::NONE);
	modbus_slave.open();

	while (true) {
		if (blue_led.is_set()) {
			DelayMS(2000);
			blue_led.write(false);
		}
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