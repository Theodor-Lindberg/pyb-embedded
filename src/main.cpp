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

	Button btn = board::get_board_button();
	DigitalOut blue_led = board::get_board_led(board::LED::BLUE);

	while(true) {
		if (btn.is_pressed()) {
			blue_led.toggle();
			DelayMS(500);
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