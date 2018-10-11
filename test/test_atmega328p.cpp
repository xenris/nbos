#define __atmega328p__

#define RECORD_ID "atmega328p"

#include "test.hpp"

typedef void (*ft)(void*);

static ft func = (ft)0x1234;
static void* data = (void*)0x5678;

//------------------------------------------------
// Analog to Digital

TEST(Adc0, getHardwareType) {
    ASSERT_EQ(Adc0::getHardwareType(), HardwareType::adc);
}

TEST(Adc0, enable) {
    TEST_REG_WRITE(Adc0::enable(true));
    TEST_REG_WRITE(Adc0::enable(false));
}

TEST(Adc0, start) {
    TEST_REG_WRITE(Adc0::start());
}

TEST(Adc0, value) {
    TEST_REG_READ_WRITE(Adc0::value());
}

TEST(Adc0, reference) {
    TEST_REG_WRITE(Adc0::reference(Adc0::Reference::aref));
    TEST_REG_WRITE(Adc0::reference(Adc0::Reference::avcc));
    TEST_REG_WRITE(Adc0::reference(Adc0::Reference::internal));
}

TEST(Adc0, channel) {
    TEST_REG_WRITE(Adc0::channel(Adc0::Channel::adc0));
    TEST_REG_WRITE(Adc0::channel(Adc0::Channel::adc1));
    TEST_REG_WRITE(Adc0::channel(Adc0::Channel::adc2));
    TEST_REG_WRITE(Adc0::channel(Adc0::Channel::adc3));
    TEST_REG_WRITE(Adc0::channel(Adc0::Channel::adc4));
    TEST_REG_WRITE(Adc0::channel(Adc0::Channel::adc5));
    TEST_REG_WRITE(Adc0::channel(Adc0::Channel::adc6));
    TEST_REG_WRITE(Adc0::channel(Adc0::Channel::adc7));
    TEST_REG_WRITE(Adc0::channel(Adc0::Channel::adc8));
    TEST_REG_WRITE(Adc0::channel(Adc0::Channel::vbg));
    TEST_REG_WRITE(Adc0::channel(Adc0::Channel::gnd));
}

TEST(Adc0, prescaler) {
    TEST_REG_WRITE(Adc0::prescaler(Adc0::Prescaler::div2));
    TEST_REG_WRITE(Adc0::prescaler(Adc0::Prescaler::div4));
    TEST_REG_WRITE(Adc0::prescaler(Adc0::Prescaler::div8));
    TEST_REG_WRITE(Adc0::prescaler(Adc0::Prescaler::div16));
    TEST_REG_WRITE(Adc0::prescaler(Adc0::Prescaler::div32));
    TEST_REG_WRITE(Adc0::prescaler(Adc0::Prescaler::div64));
    TEST_REG_WRITE(Adc0::prescaler(Adc0::Prescaler::div128));
}

TEST(Adc0, leftAdjust) {
    TEST_REG_WRITE(Adc0::leftAdjust(true));
    TEST_REG_WRITE(Adc0::leftAdjust(false));
}

TEST(Adc0, trigger) {
    TEST_REG_WRITE(Adc0::trigger(Adc0::Trigger::singleConversion));
    TEST_REG_WRITE(Adc0::trigger(Adc0::Trigger::freeRunning));
    TEST_REG_WRITE(Adc0::trigger(Adc0::Trigger::analogComparator));
    TEST_REG_WRITE(Adc0::trigger(Adc0::Trigger::externalInt0));
    TEST_REG_WRITE(Adc0::trigger(Adc0::Trigger::timer0CompareMatchA));
    TEST_REG_WRITE(Adc0::trigger(Adc0::Trigger::timer0Overflow));
    TEST_REG_WRITE(Adc0::trigger(Adc0::Trigger::timer1CompareMatchB));
    TEST_REG_WRITE(Adc0::trigger(Adc0::Trigger::timer1Overflow));
    TEST_REG_WRITE(Adc0::trigger(Adc0::Trigger::timer1CaptureEvent));
}

TEST(Adc0, callback) {
    TEST_REG_WRITE(Adc0::callback(func,data));
}

TEST(Adc0, intEnable) {
    TEST_REG_WRITE(Adc0::intEnable(false));
    TEST_REG_WRITE(Adc0::intEnable(true));
}

TEST(Adc0, intFlag) {
    TEST_REG_READ_WRITE(Adc0::intFlag());
}

TEST(Adc0, intFlagClear) {
    TEST_REG_WRITE(Adc0::intFlagClear());
}

//------------------------------------------------
// External Interrupts

TEST(ExIntN, getHardwareType) {
    ASSERT_EQ(ExInt0::getHardwareType(), HardwareType::exInt);
    ASSERT_EQ(ExInt1::getHardwareType(), HardwareType::exInt);
}

TEST(ExIntN, intEnable) {
    TEST_REG_WRITE(ExInt0::intEnable(true));
    TEST_REG_WRITE(ExInt0::intEnable(false));
    TEST_REG_WRITE(ExInt1::intEnable(true));
    TEST_REG_WRITE(ExInt1::intEnable(false));
}

TEST(ExIntN, trigger) {
    TEST_REG_WRITE(ExInt0::trigger(ExInt0::Trigger::low));
    TEST_REG_WRITE(ExInt0::trigger(ExInt0::Trigger::change));
    TEST_REG_WRITE(ExInt0::trigger(ExInt0::Trigger::falling));
    TEST_REG_WRITE(ExInt0::trigger(ExInt0::Trigger::rising));

    TEST_REG_WRITE(ExInt1::trigger(ExInt1::Trigger::low));
    TEST_REG_WRITE(ExInt1::trigger(ExInt1::Trigger::change));
    TEST_REG_WRITE(ExInt1::trigger(ExInt1::Trigger::falling));
    TEST_REG_WRITE(ExInt1::trigger(ExInt1::Trigger::rising));
}

TEST(ExIntN, callback) {
    TEST_REG_WRITE(ExInt0::callback(func,data));
    TEST_REG_WRITE(ExInt1::callback(func,data));
}

TEST(ExIntN, intFlag) {
    TEST_REG_READ_WRITE(ExInt0::intFlag());
    TEST_REG_READ_WRITE(ExInt1::intFlag());
}

TEST(ExIntN, intFlagClear) {
    TEST_REG_WRITE(ExInt0::intFlagClear());
    TEST_REG_WRITE(ExInt1::intFlagClear());
}

//------------------------------------------------
// Pin Change Interrupts

TEST(PcIntN, getHardwareType) {
    ASSERT_EQ(PcInt0::getHardwareType(), HardwareType::pcInt);
    ASSERT_EQ(PcInt1::getHardwareType(), HardwareType::pcInt);
    ASSERT_EQ(PcInt2::getHardwareType(), HardwareType::pcInt);
}

TEST(PcIntN, intEnable) {
    TEST_REG_WRITE(PcInt0::intEnable(true));
    TEST_REG_WRITE(PcInt0::intEnable(false));
    TEST_REG_WRITE(PcInt1::intEnable(true));
    TEST_REG_WRITE(PcInt1::intEnable(false));
    TEST_REG_WRITE(PcInt2::intEnable(true));
    TEST_REG_WRITE(PcInt2::intEnable(false));
}

TEST(PcIntN, mask) {
    TEST_REG_WRITE(PcInt0::mask(0x64));
    TEST_REG_WRITE(PcInt1::mask(0x54));
    TEST_REG_WRITE(PcInt2::mask(0x16));
}

TEST(PcIntN, callback) {
    TEST_REG_WRITE(PcInt0::callback(func,data));
    TEST_REG_WRITE(PcInt1::callback(func,data));
    TEST_REG_WRITE(PcInt2::callback(func,data));
}

TEST(PcIntN, intFlag) {
    TEST_REG_READ_WRITE(PcInt0::intFlag());
    TEST_REG_READ_WRITE(PcInt1::intFlag());
    TEST_REG_READ_WRITE(PcInt2::intFlag());
}

TEST(PcIntN, intFlagClear) {
    TEST_REG_WRITE(PcInt0::intFlagClear());
    TEST_REG_WRITE(PcInt1::intFlagClear());
    TEST_REG_WRITE(PcInt2::intFlagClear());
}

//------------------------------------------------
// Digital Pins

TEST(PortXPinN, getHardwareType) {
    ASSERT_EQ(PortB::Pin0::getHardwareType(), HardwareType::pin);
    ASSERT_EQ(PortB::Pin7::getHardwareType(), HardwareType::pin);
    ASSERT_EQ(PortC::Pin0::getHardwareType(), HardwareType::pin);
    ASSERT_EQ(PortC::Pin6::getHardwareType(), HardwareType::pin);
    ASSERT_EQ(PortD::Pin0::getHardwareType(), HardwareType::pin);
    ASSERT_EQ(PortD::Pin7::getHardwareType(), HardwareType::pin);
}

TEST(PortXPinN, mode) {
    TEST_REG_WRITE(PortB::Pin0::mode(Pin::Mode::input));
    TEST_REG_WRITE(PortB::Pin0::mode(Pin::Mode::inputPullup));
    TEST_REG_WRITE(PortB::Pin0::mode(Pin::Mode::output));
    TEST_REG_READ_WRITE(PortB::Pin0::mode());

    TEST_REG_WRITE(PortC::Pin6::mode(Pin::Mode::input));
    TEST_REG_WRITE(PortC::Pin6::mode(Pin::Mode::inputPullup));
    TEST_REG_WRITE(PortC::Pin6::mode(Pin::Mode::output));
    TEST_REG_READ_WRITE(PortC::Pin6::mode());

    TEST_REG_WRITE(PortD::Pin3::mode(Pin::Mode::input));
    TEST_REG_WRITE(PortD::Pin3::mode(Pin::Mode::inputPullup));
    TEST_REG_WRITE(PortD::Pin3::mode(Pin::Mode::output));
    TEST_REG_READ_WRITE(PortD::Pin3::mode());
}

TEST(PortXPinN, output) {
    TEST_REG_READ_WRITE(PortB::Pin2::output());

    TEST_REG_READ_WRITE(PortC::Pin4::output());

    TEST_REG_READ_WRITE(PortD::Pin4::output());
}

TEST(PortXPinN, input) {
    TEST_REG_READ_WRITE(PortB::Pin3::input());

    TEST_REG_READ_WRITE(PortC::Pin3::input());

    TEST_REG_READ_WRITE(PortD::Pin4::input());
}

TEST(PortXPinN, toggle) {
    TEST_REG_WRITE(PortB::Pin4::toggle());
    TEST_REG_WRITE(PortC::Pin2::toggle());
    TEST_REG_WRITE(PortD::Pin5::toggle());
}

//------------------------------------------------
// Digital Ports

TEST(PortX, getHardwareType) {
    ASSERT_EQ(PortB::getHardwareType(), HardwareType::port);
    ASSERT_EQ(PortC::getHardwareType(), HardwareType::port);
    ASSERT_EQ(PortD::getHardwareType(), HardwareType::port);
}

TEST(PortX, mode) {
    TEST_REG_WRITE(PortB::mode(Pin::Mode::input));
    TEST_REG_WRITE(PortC::mode(Pin::Mode::inputPullup));
    TEST_REG_WRITE(PortD::mode(Pin::Mode::output));
}

TEST(PortX, output) {
    TEST_REG_WRITE(PortB::output(0x27));
    TEST_REG_READ_WRITE(PortB::output());

    TEST_REG_WRITE(PortC::output(0xf4));
    TEST_REG_READ_WRITE(PortC::output());

    TEST_REG_WRITE(PortD::output(0xa4));
    TEST_REG_READ_WRITE(PortD::output());
}

TEST(PortX, input) {
    TEST_REG_READ_WRITE(PortB::input());

    TEST_REG_READ_WRITE(PortC::input());

    TEST_REG_READ_WRITE(PortD::input());
}

TEST(PortX, toggle) {
    TEST_REG_WRITE(PortB::toggle(0x26));

    TEST_REG_WRITE(PortC::toggle(0xb4));

    TEST_REG_WRITE(PortD::toggle(0x82));
}

//------------------------------------------------
// Timer/Counters

TEST(Timer0, getHardwareType) {
    ASSERT_EQ(Timer0::getHardwareType(), HardwareType::timer);
}

TEST(Timer0, type) {
    ::testing::StaticAssertTypeEq<Timer0::type, uint8_t>();
}

TEST(Timer0, counter) {
    TEST_REG_WRITE(Timer0::counter(0xc4));
    TEST_REG_READ_WRITE(Timer0::counter());
}

TEST(Timer0, clock) {
    TEST_REG_WRITE(Timer0::clock(Timer0::Clock::none));
    TEST_REG_WRITE(Timer0::clock(Timer0::Clock::div1));
    TEST_REG_WRITE(Timer0::clock(Timer0::Clock::div8));
    TEST_REG_WRITE(Timer0::clock(Timer0::Clock::div64));
    TEST_REG_WRITE(Timer0::clock(Timer0::Clock::div256));
    TEST_REG_WRITE(Timer0::clock(Timer0::Clock::div1024));
    TEST_REG_WRITE(Timer0::clock(Timer0::Clock::extFalling));
    TEST_REG_WRITE(Timer0::clock(Timer0::Clock::extRising));
}

TEST(Timer0, waveform) {
    TEST_REG_WRITE(Timer0::waveform(Timer0::Waveform::normal));
    TEST_REG_WRITE(Timer0::waveform(Timer0::Waveform::pwm));
    TEST_REG_WRITE(Timer0::waveform(Timer0::Waveform::ctcOcra));
    TEST_REG_WRITE(Timer0::waveform(Timer0::Waveform::fastPwm));
    TEST_REG_WRITE(Timer0::waveform(Timer0::Waveform::pwmOcra));
    TEST_REG_WRITE(Timer0::waveform(Timer0::Waveform::fastPwmOcra));
}

TEST(Timer0, callback) {
    TEST_REG_WRITE(Timer0::callback(func,data));
}

TEST(Timer0, intEnable) {
    TEST_REG_WRITE(Timer0::intEnable(true));
    TEST_REG_WRITE(Timer0::intEnable(false));
}

TEST(Timer0, intFlag) {
    TEST_REG_READ_WRITE(Timer0::intFlag());
}

TEST(Timer0, intFlagClear) {
    TEST_REG_WRITE(Timer0::intFlagClear());
}

TEST(Timer0, outputA) {
    TEST_REG_WRITE(Timer0::OutputA::value(0xc8));
    TEST_REG_READ_WRITE(Timer0::OutputA::value());
}

TEST(Timer0, outputB) {
    TEST_REG_WRITE(Timer0::OutputB::value(0x7a));
    TEST_REG_READ_WRITE(Timer0::OutputB::value());
}

TEST(Timer0, outputAMode) {
    TEST_REG_WRITE(Timer0::OutputA::mode(Timer0::OutputA::Mode::disconnected));
    TEST_REG_WRITE(Timer0::OutputA::mode(Timer0::OutputA::Mode::toggle));
    TEST_REG_WRITE(Timer0::OutputA::mode(Timer0::OutputA::Mode::clear));
    TEST_REG_WRITE(Timer0::OutputA::mode(Timer0::OutputA::Mode::set));
}

TEST(Timer0, outputBMode) {
    TEST_REG_WRITE(Timer0::OutputB::mode(Timer0::OutputB::Mode::disconnected));
    TEST_REG_WRITE(Timer0::OutputB::mode(Timer0::OutputB::Mode::toggle));
    TEST_REG_WRITE(Timer0::OutputB::mode(Timer0::OutputB::Mode::clear));
    TEST_REG_WRITE(Timer0::OutputB::mode(Timer0::OutputB::Mode::set));
}

TEST(Timer0, outputACallback) {
    TEST_REG_WRITE(Timer0::OutputA::callback(func,data));
}

TEST(Timer0, outputBCallback) {
    TEST_REG_WRITE(Timer0::OutputB::callback(func,data));
}

TEST(Timer0, outputAIntEnable) {
    TEST_REG_WRITE(Timer0::OutputA::intEnable(true));
    TEST_REG_WRITE(Timer0::OutputA::intEnable(false));
}

TEST(Timer0, outputBIntEnable) {
    TEST_REG_WRITE(Timer0::OutputB::intEnable(true));
    TEST_REG_WRITE(Timer0::OutputB::intEnable(false));
}

TEST(Timer0, outputAIntFlag) {
    TEST_REG_READ_WRITE(Timer0::OutputA::intFlag());
}

TEST(Timer0, outputBIntFlag) {
    TEST_REG_READ_WRITE(Timer0::OutputB::intFlag());
}

TEST(Timer0, outputAIntFlagClear) {
    TEST_REG_WRITE(Timer0::OutputA::intFlagClear());
}

TEST(Timer0, outputBIntFlagClear) {
    TEST_REG_WRITE(Timer0::OutputB::intFlagClear());
}

TEST(Timer1, getHardwareType) {
    ASSERT_EQ(Timer1::getHardwareType(), HardwareType::timer);
}

TEST(Timer1, type) {
    ::testing::StaticAssertTypeEq<Timer1::type, uint16_t>();
}

TEST(Timer1, counter) {
    TEST_REG_WRITE(Timer1::counter(0x7c8a));
    TEST_REG_READ_WRITE(Timer1::counter());
}

TEST(Timer1, clock) {
    TEST_REG_WRITE(Timer1::clock(Timer1::Clock::none));
    TEST_REG_WRITE(Timer1::clock(Timer1::Clock::div1));
    TEST_REG_WRITE(Timer1::clock(Timer1::Clock::div8));
    TEST_REG_WRITE(Timer1::clock(Timer1::Clock::div64));
    TEST_REG_WRITE(Timer1::clock(Timer1::Clock::div256));
    TEST_REG_WRITE(Timer1::clock(Timer1::Clock::div1024));
    TEST_REG_WRITE(Timer1::clock(Timer1::Clock::extFalling));
    TEST_REG_WRITE(Timer1::clock(Timer1::Clock::extRising));
}

TEST(Timer1, waveform) {
    TEST_REG_WRITE(Timer1::waveform(Timer1::Waveform::normal));
    TEST_REG_WRITE(Timer1::waveform(Timer1::Waveform::pwm));
    TEST_REG_WRITE(Timer1::waveform(Timer1::Waveform::ctcOcra));
    TEST_REG_WRITE(Timer1::waveform(Timer1::Waveform::fastPwm));
    TEST_REG_WRITE(Timer1::waveform(Timer1::Waveform::pwmOcra));
    TEST_REG_WRITE(Timer1::waveform(Timer1::Waveform::fastPwmOcra));
}

TEST(Timer1, callback) {
    TEST_REG_WRITE(Timer1::callback(func,data));
}

TEST(Timer1, intEnable) {
    TEST_REG_WRITE(Timer1::intEnable(true));
    TEST_REG_WRITE(Timer1::intEnable(false));
}

TEST(Timer1, intFlag) {
    TEST_REG_READ_WRITE(Timer1::intFlag());
}

TEST(Timer1, intFlagClear) {
    TEST_REG_WRITE(Timer1::intFlagClear());
}

TEST(Timer1, outputA) {
    TEST_REG_WRITE(Timer1::OutputA::value(0xe8d9));
    TEST_REG_READ_WRITE(Timer1::OutputA::value());
}

TEST(Timer1, outputB) {
    TEST_REG_WRITE(Timer1::OutputB::value(0x7a8d));
    TEST_REG_READ_WRITE(Timer1::OutputB::value());
}

TEST(Timer1, outputAMode) {
    TEST_REG_WRITE(Timer1::OutputA::mode(Timer1::OutputA::Mode::disconnected));
    TEST_REG_WRITE(Timer1::OutputA::mode(Timer1::OutputA::Mode::toggle));
    TEST_REG_WRITE(Timer1::OutputA::mode(Timer1::OutputA::Mode::clear));
    TEST_REG_WRITE(Timer1::OutputA::mode(Timer1::OutputA::Mode::set));
}

TEST(Timer1, outputBMode) {
    TEST_REG_WRITE(Timer1::OutputB::mode(Timer1::OutputB::Mode::disconnected));
    TEST_REG_WRITE(Timer1::OutputB::mode(Timer1::OutputB::Mode::toggle));
    TEST_REG_WRITE(Timer1::OutputB::mode(Timer1::OutputB::Mode::clear));
    TEST_REG_WRITE(Timer1::OutputB::mode(Timer1::OutputB::Mode::set));
}

TEST(Timer1, outputACallback) {
    TEST_REG_WRITE(Timer1::OutputA::callback(func,data));
}

TEST(Timer1, outputBCallback) {
    TEST_REG_WRITE(Timer1::OutputB::callback(func,data));
}

TEST(Timer1, outputAIntEnable) {
    TEST_REG_WRITE(Timer1::OutputA::intEnable(true));
    TEST_REG_WRITE(Timer1::OutputA::intEnable(false));
}

TEST(Timer1, outputBIntEnable) {
    TEST_REG_WRITE(Timer1::OutputB::intEnable(true));
    TEST_REG_WRITE(Timer1::OutputB::intEnable(false));
}

TEST(Timer1, outputAIntFlag) {
    TEST_REG_READ_WRITE(Timer1::OutputA::intFlag());
}

TEST(Timer1, outputBIntFlag) {
    TEST_REG_READ_WRITE(Timer1::OutputB::intFlag());
}

TEST(Timer1, outputAIntFlagClear) {
    TEST_REG_WRITE(Timer1::OutputA::intFlagClear());
}

TEST(Timer1, outputBIntFlagClear) {
    TEST_REG_WRITE(Timer1::OutputB::intFlagClear());
}

TEST(Timer2, getHardwareType) {
    ASSERT_EQ(Timer2::getHardwareType(), HardwareType::timer);
}

TEST(Timer2, type) {
    ::testing::StaticAssertTypeEq<Timer2::type, uint8_t>();
}

TEST(Timer2, counter) {
    TEST_REG_WRITE(Timer2::counter(0x23));
    TEST_REG_READ_WRITE(Timer2::counter());
}

TEST(Timer2, clock) {
    TEST_REG_WRITE(Timer2::clock(Timer2::Clock::none));
    TEST_REG_WRITE(Timer2::clock(Timer2::Clock::div1));
    TEST_REG_WRITE(Timer2::clock(Timer2::Clock::div8));
    TEST_REG_WRITE(Timer2::clock(Timer2::Clock::div32));
    TEST_REG_WRITE(Timer2::clock(Timer2::Clock::div64));
    TEST_REG_WRITE(Timer2::clock(Timer2::Clock::div128));
    TEST_REG_WRITE(Timer2::clock(Timer2::Clock::div256));
    TEST_REG_WRITE(Timer2::clock(Timer2::Clock::div1024));
}

TEST(Timer2, waveform) {
    TEST_REG_WRITE(Timer2::waveform(Timer2::Waveform::normal));
    TEST_REG_WRITE(Timer2::waveform(Timer2::Waveform::pwm));
    TEST_REG_WRITE(Timer2::waveform(Timer2::Waveform::ctcOcra));
    TEST_REG_WRITE(Timer2::waveform(Timer2::Waveform::fastPwm));
    TEST_REG_WRITE(Timer2::waveform(Timer2::Waveform::pwmOcra));
    TEST_REG_WRITE(Timer2::waveform(Timer2::Waveform::fastPwmOcra));
}

TEST(Timer2, callback) {
    TEST_REG_WRITE(Timer2::callback(func,data));
}

TEST(Timer2, intEnable) {
    TEST_REG_WRITE(Timer2::intEnable(true));
    TEST_REG_WRITE(Timer2::intEnable(false));
}

TEST(Timer2, intFlag) {
    TEST_REG_READ_WRITE(Timer2::intFlag());
}

TEST(Timer2, intFlagClear) {
    TEST_REG_WRITE(Timer2::intFlagClear());
}

TEST(Timer2, outputA) {
    TEST_REG_WRITE(Timer2::OutputA::value(0xed));
    TEST_REG_READ_WRITE(Timer2::OutputA::value());
}

TEST(Timer2, outputB) {
    TEST_REG_WRITE(Timer2::OutputB::value(0xd8));
    TEST_REG_READ_WRITE(Timer2::OutputB::value());
}

TEST(Timer2, outputAMode) {
    TEST_REG_WRITE(Timer2::OutputA::mode(Timer2::OutputA::Mode::disconnected));
    TEST_REG_WRITE(Timer2::OutputA::mode(Timer2::OutputA::Mode::toggle));
    TEST_REG_WRITE(Timer2::OutputA::mode(Timer2::OutputA::Mode::clear));
    TEST_REG_WRITE(Timer2::OutputA::mode(Timer2::OutputA::Mode::set));
}

TEST(Timer2, outputBMode) {
    TEST_REG_WRITE(Timer2::OutputB::mode(Timer2::OutputB::Mode::disconnected));
    TEST_REG_WRITE(Timer2::OutputB::mode(Timer2::OutputB::Mode::toggle));
    TEST_REG_WRITE(Timer2::OutputB::mode(Timer2::OutputB::Mode::clear));
    TEST_REG_WRITE(Timer2::OutputB::mode(Timer2::OutputB::Mode::set));
}

TEST(Timer2, outputACallback) {
    TEST_REG_WRITE(Timer2::OutputA::callback(func,data));
}

TEST(Timer2, outputBCallback) {
    TEST_REG_WRITE(Timer2::OutputB::callback(func,data));
}

TEST(Timer2, outputAIntEnable) {
    TEST_REG_WRITE(Timer2::OutputA::intEnable(true));
    TEST_REG_WRITE(Timer2::OutputA::intEnable(false));
}

TEST(Timer2, outputBIntEnable) {
    TEST_REG_WRITE(Timer2::OutputB::intEnable(true));
    TEST_REG_WRITE(Timer2::OutputB::intEnable(false));
}

TEST(Timer2, outputAIntFlag) {
    TEST_REG_READ_WRITE(Timer2::OutputA::intFlag());
}

TEST(Timer2, outputBIntFlag) {
    TEST_REG_READ_WRITE(Timer2::OutputB::intFlag());
}

TEST(Timer2, outputAIntFlagClear) {
    TEST_REG_WRITE(Timer2::OutputA::intFlagClear());
}

TEST(Timer2, outputBIntFlagClear) {
    TEST_REG_WRITE(Timer2::OutputB::intFlagClear());
}

//------------------------------------------------
// Usart

TEST(Usart0, getHardwareType) {
    ASSERT_EQ(Usart0::getHardwareType(), HardwareType::usart);
}

TEST(Usart0, mode) {
    TEST_REG_WRITE(Usart0::mode(Usart0::Mode::asynchronous));
    TEST_REG_WRITE(Usart0::mode(Usart0::Mode::synchronous));
    TEST_REG_WRITE(Usart0::mode(Usart0::Mode::masterSpi));
}

TEST(Usart0, parity) {
    TEST_REG_WRITE(Usart0::parity(Usart0::Parity::disabled));
    TEST_REG_WRITE(Usart0::parity(Usart0::Parity::even));
    TEST_REG_WRITE(Usart0::parity(Usart0::Parity::odd));
}

TEST(Usart0, stopBits) {
    TEST_REG_WRITE(Usart0::stopBits(Usart0::StopBits::bits1));
    TEST_REG_WRITE(Usart0::stopBits(Usart0::StopBits::bits2));
}

TEST(Usart0, characterSize) {
    TEST_REG_WRITE(Usart0::characterSize(Usart0::CharacterSize::size5));
    TEST_REG_WRITE(Usart0::characterSize(Usart0::CharacterSize::size6));
    TEST_REG_WRITE(Usart0::characterSize(Usart0::CharacterSize::size7));
    TEST_REG_WRITE(Usart0::characterSize(Usart0::CharacterSize::size8));
    TEST_REG_WRITE(Usart0::characterSize(Usart0::CharacterSize::size9));
}

TEST(Usart0, polarity) {
    TEST_REG_WRITE(Usart0::polarity(Usart0::Polarity::txRisingRxFalling));
    TEST_REG_WRITE(Usart0::polarity(Usart0::Polarity::txFallingRxRising));
}

TEST(Usart0, baud) {
    TEST_REG_WRITE(Usart0::baud(0xe819));
}

TEST(Usart0, use2X) {
    TEST_REG_WRITE(Usart0::use2X(true));
    TEST_REG_WRITE(Usart0::use2X(false));
}

TEST(Usart0, receiverEnable) {
    TEST_REG_WRITE(Usart0::receiverEnable(true));
    TEST_REG_WRITE(Usart0::receiverEnable(false));
}

TEST(Usart0, transmitterEnable) {
    TEST_REG_WRITE(Usart0::transmitterEnable(true));
    TEST_REG_WRITE(Usart0::transmitterEnable(false));
}

TEST(Usart0, multiprocessorCummunicationMode) {
    TEST_REG_WRITE(Usart0::multiprocessorCummunicationMode(true));
    TEST_REG_WRITE(Usart0::multiprocessorCummunicationMode(false));
}

TEST(Usart0, rxCompleteIntEnable) {
    TEST_REG_WRITE(Usart0::rxCompleteIntEnable(true));
    TEST_REG_WRITE(Usart0::rxCompleteIntEnable(false));
}

TEST(Usart0, txCompleteIntEnable) {
    TEST_REG_WRITE(Usart0::txCompleteIntEnable(true));
    TEST_REG_WRITE(Usart0::txCompleteIntEnable(false));
}

TEST(Usart0, dataRegisterEmptyIntEnable) {
    TEST_REG_WRITE(Usart0::dataRegisterEmptyIntEnable(true));
    TEST_REG_WRITE(Usart0::dataRegisterEmptyIntEnable(false));
}

TEST(Usart0, rxCompleteCallback) {
    TEST_REG_WRITE(Usart0::rxCompleteCallback(func,data));
}

TEST(Usart0, txCompleteCallback) {
    TEST_REG_WRITE(Usart0::txCompleteCallback(func,data));
}

TEST(Usart0, dataRegisterEmptyCallback) {
    TEST_REG_WRITE(Usart0::dataRegisterEmptyCallback(func,data));
}

TEST(Usart0, push) {
    TEST_REG_WRITE(Usart0::push(0x18));
}

TEST(Usart0, push9) {
    TEST_REG_WRITE(Usart0::push9(0x3261));
}

TEST(Usart0, pop) {
    TEST_REG_READ_WRITE(Usart0::pop());
}

TEST(Usart0, pop9) {
    TEST_REG_READ_WRITE(Usart0::pop9());
}

TEST(Usart0, frameError) {
    TEST_REG_READ_WRITE(Usart0::frameError());
}

TEST(Usart0, frameErrorClear) {
    TEST_REG_WRITE(Usart0::frameErrorClear());
}

TEST(Usart0, dataOverRun) {
    TEST_REG_READ_WRITE(Usart0::dataOverRun());
}

TEST(Usart0, dataOverRunClear) {
    TEST_REG_WRITE(Usart0::dataOverRunClear());
}

TEST(Usart0, parityError) {
    TEST_REG_READ_WRITE(Usart0::parityError());
}

TEST(Usart0, parityErrorClear) {
    TEST_REG_WRITE(Usart0::parityErrorClear());
}

//------------------------------------------------
// Spi

TEST(Spi0, getHardwareType) {
    ASSERT_EQ(Spi0::getHardwareType(), HardwareType::spi);
}

TEST(Spi0, enable) {
    TEST_REG_WRITE(Spi0::enable(true));
    TEST_REG_WRITE(Spi0::enable(false));
}

TEST(Spi0, intEnable) {
    TEST_REG_WRITE(Spi0::intEnable(true));
    TEST_REG_WRITE(Spi0::intEnable(false));
}

TEST(Spi0, dataOrder) {
    TEST_REG_WRITE(Spi0::dataOrder(Spi0::DataOrder::msbFirst));
    TEST_REG_WRITE(Spi0::dataOrder(Spi0::DataOrder::lsbFirst));
}

TEST(Spi0, masterSlave) {
    TEST_REG_WRITE(Spi0::masterSlave(Spi0::MasterSlave::master));
    TEST_REG_WRITE(Spi0::masterSlave(Spi0::MasterSlave::slave));
}

TEST(Spi0, polarity) {
    TEST_REG_WRITE(Spi0::polarity(Spi0::Polarity::leadingRisingTrailingFalling));
    TEST_REG_WRITE(Spi0::polarity(Spi0::Polarity::leadingFallingTrailingRising));
}

TEST(Spi0, phase) {
    TEST_REG_WRITE(Spi0::phase(Spi0::Phase::leadingSampleTrailingSetup));
    TEST_REG_WRITE(Spi0::phase(Spi0::Phase::leadingSetupTrailingSample));
}

TEST(Spi0, clock) {
    TEST_REG_WRITE(Spi0::clock(Spi0::Clock::div2));
    TEST_REG_WRITE(Spi0::clock(Spi0::Clock::div4));
    TEST_REG_WRITE(Spi0::clock(Spi0::Clock::div8));
    TEST_REG_WRITE(Spi0::clock(Spi0::Clock::div16));
    TEST_REG_WRITE(Spi0::clock(Spi0::Clock::div32));
    TEST_REG_WRITE(Spi0::clock(Spi0::Clock::div64));
}

TEST(Spi0, intFlag) {
    TEST_REG_READ_WRITE(Spi0::intFlag());
}

TEST(Spi0, intFlagClear) {
    TEST_REG_WRITE(Spi0::intFlagClear());
}

TEST(Spi0, collisionFlag) {
    TEST_REG_READ_WRITE(Spi0::collisionFlag());
}

TEST(Spi0, collisionFlagClear) {
    TEST_REG_WRITE(Spi0::collisionFlagClear());
}

TEST(Spi0, data) {
    TEST_REG_READ_WRITE(Spi0::data());
    TEST_REG_WRITE(Spi0::data(0x00));
    TEST_REG_WRITE(Spi0::data(0xFF));
    TEST_REG_WRITE(Spi0::data(0x4E));
}
