#ifndef FLASH_HPP
#define FLASH_HPP

#include <nbavr.hpp>

template <class ledPin>
class Flash : public Task {
    Clock& clock;
    Stream<char>& stdin;
    static const uint32_t pulseLength = MS_TO_TICKS(50);

public:
    Flash(Clock& clock, Stream<char>& stdin) : clock(clock), stdin(stdin) {
        ledPin::direction(ledPin::Direction::Output);
    }

private:
    void loop() override {
        ledPin::value(ledPin::Value::Low);

        char c;

        if(stdin.pop(&c)) {
            stdin.clear();
            ledPin::value(ledPin::Value::High);
            delay(clock, pulseLength);
        }
    }
};

#endif
