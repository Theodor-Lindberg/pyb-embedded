#pragma once

class DigitalOutBase {
	public:
	virtual void write(const bool state) = 0;
	virtual void toggle() = 0;
	virtual bool is_set() = 0;
	virtual ~DigitalOutBase() = default;
};