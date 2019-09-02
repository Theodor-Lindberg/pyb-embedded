class ITimerHook {
	public:
	virtual ~ITimerHook() {}
	virtual void timer_it_hook() = 0;
};