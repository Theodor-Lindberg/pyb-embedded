#pragma once 
class IUsartHook {
	public:
	virtual ~IUsartHook() {}
	virtual void rx_it_hook() = 0;
};