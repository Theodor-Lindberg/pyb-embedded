#include "catch.hpp"
#include "Button.hpp"

TEST_CASE( "Button pressed active high", "[single-file]" ) {
    DigitalIn di(Port::A, Pin::PIN1, Pull::DOWN);
    Button button(di, true);
    REQUIRE(button.is_pressed() == false);
    di.set(true);
    REQUIRE(button.is_pressed());
    di.set(false);
    REQUIRE(button.is_pressed() == false);
}

TEST_CASE( "Button pressed active low", "[single-file]" ) {
    DigitalIn di(Port::A, Pin::PIN1, Pull::DOWN);
    di.set(true);
    Button button(di, false);
    REQUIRE(button.is_pressed() == false);
    di.set(false);
    REQUIRE(button.is_pressed());
    di.set(true);
    REQUIRE(button.is_pressed() == false);
}