/// # {{Digital IO Pins}}

/// N is the pin id (0, 1, 2, etc).

/// ## Example

/// ```c++
/// PortB::Pin5::mode(Pin::Mode::output);
///
/// PortB::Pin5::output(Pin::Value::high);
///
/// while(true) {
///     PortB::Pin5::toggle();
///     nbos::block();
/// }
/// ```

#include "hardware/chip.hpp"
#include "macros.hpp"
#include "type.hpp"

#ifndef NBOS_BASE_PIN
#define NBOS_BASE_PIN

#define MODE(A) CAT(CHIP_PIN_MODE_, A, _ID)

namespace nbos::hw {

/// ## class {{Pin}}
struct Pin {
    Pin() = delete;
    Pin& operator=(const Pin&) = delete;
    Pin(const Pin&) = delete;

    /// #### enum {{Pin::Mode}}
    /// * input
    /// * inputPullup
    /// * output
    /// * inputAnalog
    /// * inputFloating
    /// * inputPullUpDown
    /// * outputGeneralPushPull10MHz
    /// * outputGeneralOpenDrain10MHz
    /// * outputAlternatePushPull10MHz
    /// * outputAlternateOpenDrain10MHz
    /// * outputGeneralPushPull2MHz
    /// * outputGeneralOpenDrain2MHz
    /// * outputAlternatePushPull2MHz
    /// * outputAlternateOpenDrain2MHz
    /// * outputGeneralPushPull50MHz
    /// * outputGeneralOpenDrain50MHz
    /// * outputAlternatePushPull50MHz
    /// * outputAlternateOpenDrain50MHz
    enum class Mode : uint8_t {
        #if DEFINED(MODE(INPUT))
            input = MODE(INPUT),
        #endif

        #if DEFINED(MODE(INPUT_PULLUP))
            inputPullup = MODE(INPUT_PULLUP),
        #endif

        #if DEFINED(MODE(OUTPUT))
            output = MODE(OUTPUT),
        #endif

        #if DEFINED(MODE(INPUT_ANALOG))
            inputAnalog = MODE(INPUT_ANALOG),
        #endif

        #if DEFINED(MODE(INPUT_FLOATING))
            inputFloating = MODE(INPUT_FLOATING),
        #endif

        #if DEFINED(MODE(INPUT_PULLUPDOWN))
            inputPullUpDown = MODE(INPUT_PULLUPDOWN),
        #endif

        #if DEFINED(MODE(OUTPUT_GENERAL_PUSH_PULL_10MHZ))
            outputGeneralPushPull10MHz = MODE(OUTPUT_GENERAL_PUSH_PULL_10MHZ),
        #endif

        #if DEFINED(MODE(OUTPUT_GENERAL_OPEN_DRAIN_10MHZ))
            outputGeneralOpenDrain10MHz = MODE(OUTPUT_GENERAL_OPEN_DRAIN_10MHZ),
        #endif

        #if DEFINED(MODE(OUTPUT_ALTERNATE_PUSH_PULL_10MHZ))
            outputAlternatePushPull10MHz = MODE(OUTPUT_ALTERNATE_PUSH_PULL_10MHZ),
        #endif

        #if DEFINED(MODE(OUTPUT_ALTERNATE_OPEN_DRAIN_10MHZ))
            outputAlternateOpenDrain10MHz = MODE(OUTPUT_ALTERNATE_OPEN_DRAIN_10MHZ),
        #endif

        #if DEFINED(MODE(OUTPUT_GENERAL_PUSH_PULL_2MHZ))
            outputGeneralPushPull2MHz = MODE(OUTPUT_GENERAL_PUSH_PULL_2MHZ),
        #endif

        #if DEFINED(MODE(OUTPUT_GENERAL_OPEN_DRAIN_2MHZ))
            outputGeneralOpenDrain2MHz = MODE(OUTPUT_GENERAL_OPEN_DRAIN_2MHZ),
        #endif

        #if DEFINED(MODE(OUTPUT_ALTERNATE_PUSH_PULL_2MHZ))
            outputAlternatePushPull2MHz = MODE(OUTPUT_ALTERNATE_PUSH_PULL_2MHZ),
        #endif

        #if DEFINED(MODE(OUTPUT_ALTERNATE_OPEN_DRAIN_2MHZ))
            outputAlternateOpenDrain2MHz = MODE(OUTPUT_ALTERNATE_OPEN_DRAIN_2MHZ),
        #endif

        #if DEFINED(MODE(OUTPUT_GENERAL_PUSH_PULL_50MHZ))
            outputGeneralPushPull50MHz = MODE(OUTPUT_GENERAL_PUSH_PULL_50MHZ),
        #endif

        #if DEFINED(MODE(OUTPUT_GENERAL_OPEN_DRAIN_50MHZ))
            outputGeneralOpenDrain50MHz = MODE(OUTPUT_GENERAL_OPEN_DRAIN_50MHZ),
        #endif

        #if DEFINED(MODE(OUTPUT_ALTERNATE_PUSH_PULL_50MHZ))
            outputAlternatePushPull50MHz = MODE(OUTPUT_ALTERNATE_PUSH_PULL_50MHZ),
        #endif

        #if DEFINED(MODE(OUTPUT_ALTERNATE_OPEN_DRAIN_50MHZ))
            outputAlternateOpenDrain50MHz = MODE(OUTPUT_ALTERNATE_OPEN_DRAIN_50MHZ),
        #endif
    };

    /// #### enum {{Pin::Value}}
    /// * low
    /// * high
    enum class Value : uint8_t {
        low = 0,
        high = 1,
    };
};

} // nbos::hw


#undef MODE

#endif

#ifdef PortX

#include "loopj"

#define N _J
#define PinN CAT(Pin, N)
#define PIN_N(A) CAT(CHIP_PIN_, X, N, _, A)

#ifdef _J
    #if CAT(CHIP_PIN_, X, N)

//------------------------------------------------------------------

/// ## Class {{PinN}} : Pin
struct PinN : Pin {
    PinN() = delete;
    PinN& operator=(const PinN&) = delete;
    PinN(const PinN&) = delete;

    /// #### static [[HardwareType]] getHardwareType()
    static constexpr HardwareType getHardwareType() {
        return HardwareType::pin;
    }

    /// #### static void mode([[Pin::Mode]] m)
    static force_inline void mode(Mode m) {
        setBit_(REG(PIN_N(MODE_BIT_0_REG)), PIN_N(MODE_BIT_0_BIT), uint8_t(m) & 0x01);

        #if DEFINED(PIN_N(MODE_BIT_1_BIT))
            setBit_(REG(PIN_N(MODE_BIT_1_REG)), PIN_N(MODE_BIT_1_BIT), uint8_t(m) & 0x02);
        #endif

        #if DEFINED(PIN_N(MODE_BIT_2_BIT))
            setBit_(REG(PIN_N(MODE_BIT_2_REG)), PIN_N(MODE_BIT_2_BIT), uint8_t(m) & 0x04);
        #endif

        #if DEFINED(PIN_N(MODE_BIT_3_BIT))
            setBit_(REG(PIN_N(MODE_BIT_3_REG)), PIN_N(MODE_BIT_3_BIT), uint8_t(m) & 0x08);
        #endif
    }

    /// #### static [[Pin::Mode]] mode()
    static force_inline Mode mode() {
        uint8_t m = 0;

        #if DEFINED(PIN_N(MODE_BIT_0_BIT))
            m |= getBit(REG(PIN_N(MODE_BIT_0_REG)), PIN_N(MODE_BIT_0_BIT)) << 0;
        #endif

        #if DEFINED(PIN_N(MODE_BIT_1_BIT))
            m |= getBit(REG(PIN_N(MODE_BIT_1_REG)), PIN_N(MODE_BIT_1_BIT)) << 1;
        #endif

        #if DEFINED(PIN_N(MODE_BIT_2_BIT))
            m |= getBit(REG(PIN_N(MODE_BIT_2_REG)), PIN_N(MODE_BIT_2_BIT)) << 2;
        #endif

        #if DEFINED(PIN_N(MODE_BIT_3_BIT))
            m |= getBit(REG(PIN_N(MODE_BIT_3_REG)), PIN_N(MODE_BIT_3_BIT)) << 3;
        #endif

        return Mode(m);
    }

    /// #### static void output([[Pin::Value]] v)
    static force_inline void output(Value v) {
        setBit_(REG(PIN_N(OUTPUT_BIT_0_REG)), PIN_N(OUTPUT_BIT_0_BIT), v == Value::high);
    }

    /// #### static [[Pin::Value]] output()
    static force_inline Value output() {
        return getBit(REG(PIN_N(OUTPUT_BIT_0_REG)), PIN_N(OUTPUT_BIT_0_BIT)) ? Value::high : Value::low;
    }

    /// #### static [[Pin::Value]] input()
    static force_inline Value input() {
        return getBit(REG(PIN_N(INPUT_BIT_0_REG)), PIN_N(INPUT_BIT_0_BIT)) ? Value::high : Value::low;
    }

    #if DEFINED(PIN_N(TOGGLE_BIT_0_BIT))
        /// #### static void toggle()
        static force_inline void toggle() {
            setBit_(REG(PIN_N(TOGGLE_BIT_0_REG)), PIN_N(TOGGLE_BIT_0_BIT), true);
        }
    #endif
};

//------------------------------------------------------------------

    #endif

    #include "pin.hpp"
#endif

#undef N
#undef PinN
#undef PIN_N

#endif
