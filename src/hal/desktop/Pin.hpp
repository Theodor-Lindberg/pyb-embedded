enum PinMode {
    INPUT = 0,
    OUTPUT,
    ALTERNATE,
    ANALOG
};

struct Pin {
    const int number;
    const PinMode mode;
    Pin(int number, PinMode mode):
    number(number), mode(mode) {}
};