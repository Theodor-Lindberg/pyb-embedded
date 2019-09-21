#pragma once
#include "USART_Driver.hpp"
#include "Timer.hpp"
#include "IUsartHook.hpp"
#include "ITimerHook.hpp"

class ModbusSlave : IUsartHook, ITimerHook {
	public:
	ModbusSlave(SerialDriver* const serial_driver, TIMER tim);
	ModbusSlave(SerialDriver* const serial_driver, TIMER tim, uint8_t ID, BAUDRATE baudrate, STOPBITS stop_bits, PARITY parity);
	void open();
	void close();
	void set_id(uint8_t ID);
	void process_packet();
	virtual void rx_it_hook();
	virtual void timer_it_hook();
	private:
	/**
	 * @brief Modbus Function Code
	 */
	enum class FC : uint8_t {
		FC01 = 0x1U,	// Read Coil Status
		FC02 = 0x2U,	// Read Input Status
		FC03 = 0x3U,	// Read Holding Registers
		FC04 = 0x4U,	// Read Input Registers
		FC05 = 0x5U,	// Force Single Coil
		FC06 = 0x6U,	// Preset Single Register
		FC15 = 0xFU,	// Force Multiple Coils
		FC16 = 0x10U	// Preset Multiple Registers
	};

	/**
	 * @brief Modbus Exception Code
	 */
	enum class Exception : uint8_t {
		None = 0x0U,
		Illegal_Function = 0x1U,
		Illegal_Data_Address = 0x2U,
		Illegal_Data_Value = 0x3U,
		Slave_Device_Failure = 0x4U,
		Acknowledge = 0x5U,
		Slave_Device_Busy = 0x6U,
		Negative_Acknowledge = 0x7U,
		Memory_Parity_Error = 0x8U,
		Gateway_Path_Unavailable = 0xAU,
		Gateway_Target_Device_Failed_To_Respond = 0xBU,
		Indicator_Mask = 0x80U	// Used to mask the function code in response
	};
	static constexpr uint8_t ID_IDX = 0U;
	static constexpr uint8_t FC_IDX = 1U;
	SerialDriver* const serial_driver;
	Timer timer;
	uint8_t mb_id;
	uint8_t receive_index;
	uint8_t recieve_buffer[9];
	uint32_t response_length;
	uint8_t response_buffer[9];
	uint16_t calculate_crc(const uint8_t* const buffer, uint32_t count) const;
	bool is_package_valid() const;
	uint32_t calculate_end_frame(BAUDRATE baudrate) const;
	Exception handle_fc1();
};