/// # Analog to Digital Converter

/// ## Example

/// ```c++
/// // Start the analog to digital converter.

/// atomic {
///     Adc::reference(Adc::Reference::AVCC);
///     Adc::channel(Adc::Channel::ADC1);
///     Adc::prescaler(Adc::Prescaler::Div128);
///     Adc::trigger(Adc::Trigger::SingleConversion);
/// }

/// Adc::start();

/// // In the main loop.

/// if(Adc::intFlag()) {
///     adcValue = Adc::value();

///     Adc::intFlagClear();
/// } else {
///     // Conversion not done yet.
/// }
/// ```

#ifndef NBOS_ADC_HPP

#include "callbacks.hpp"
#include "chip.hpp"
#include "hardwaretype.hpp"
#include "macros.hpp"
#include "system.hpp"

/// #### macro INCLUDE_ADC_CALLBACK(N)
/// Include this to use Adc callbacks.
#define INCLUDE_ADC_CALLBACK(N) MAKE_CALLBACK(ADC, N)

#include "loopi"

#ifdef _I
    #define N _I
    #define AdcN CAT(Adc, N)
    #define ADC_N(A) CAT(CHIP_ADC_, N, _, A)
    #define _ADC_N(A) UNDERLINE(ADC, N, A)

    #if CAT(CHIP_ADC_, N)

//------------------------------------------------------------------

namespace nbos::hw {

MAKE_CALLBACK_HEADER(ADC, N);

/// ## class Adc
struct AdcN {
    AdcN() = delete;
    AdcN& operator=(const AdcN&) = delete;
    AdcN(const AdcN&) = delete;

    /// #### enum Reference
    /// * aref
    /// * avcc
    /// * internal
    /// * internal_1_1
    /// * internal_2_56
    /// * internal_2_56_cap
    enum class Reference : uint8_t {
        #if DEFINED(ADC_N(REFERENCE_AREF_ID))
            aref = ADC_N(REFERENCE_AREF_ID),
        #endif

        #if DEFINED(ADC_N(REFERENCE_AVCC_ID))
            avcc = ADC_N(REFERENCE_AVCC_ID),
        #endif

        #if DEFINED(ADC_N(REFERENCE_INTERNAL_ID))
            internal = ADC_N(REFERENCE_INTERNAL_ID),
        #endif

        #if DEFINED(ADC_N(REFERENCE_INTERNAL_1_1_ID))
            internal_1_1 = ADC_N(REFERENCE_INTERNAL_1_1_ID),
        #endif

        #if DEFINED(ADC_N(REFERENCE_INTERNAL_2_56_ID))
            internal_2_56 = ADC_N(REFERENCE_INTERNAL_2_56_ID),
        #endif

        #if DEFINED(ADC_N(REFERENCE_INTERNAL_2_56_CAP_ID))
            internal_2_56_cap = ADC_N(REFERENCE_INTERNAL_2_56_CAP_ID),
        #endif
    };

    /// #### enum Channel
    /// * adc0
    /// * adc1
    /// * adc2
    /// * adc3
    /// * adc4
    /// * adc5
    /// * adc6
    /// * adc7
    /// * adc8
    /// * vbg
    /// * gnd
    enum class Channel : uint8_t {
        #if DEFINED(ADC_N(CHANNEL_0_ID))
            adc0 = ADC_N(CHANNEL_0_ID),
        #endif

        #if DEFINED(ADC_N(CHANNEL_1_ID))
            adc1 = ADC_N(CHANNEL_1_ID),
        #endif

        #if DEFINED(ADC_N(CHANNEL_2_ID))
            adc2 = ADC_N(CHANNEL_2_ID),
        #endif

        #if DEFINED(ADC_N(CHANNEL_3_ID))
            adc3 = ADC_N(CHANNEL_3_ID),
        #endif

        #if DEFINED(ADC_N(CHANNEL_4_ID))
            adc4 = ADC_N(CHANNEL_4_ID),
        #endif

        #if DEFINED(ADC_N(CHANNEL_5_ID))
            adc5 = ADC_N(CHANNEL_5_ID),
        #endif

        #if DEFINED(ADC_N(CHANNEL_6_ID))
            adc6 = ADC_N(CHANNEL_6_ID),
        #endif

        #if DEFINED(ADC_N(CHANNEL_7_ID))
            adc7 = ADC_N(CHANNEL_7_ID),
        #endif

        #if DEFINED(ADC_N(CHANNEL_8_ID))
            adc8 = ADC_N(CHANNEL_8_ID),
        #endif

        #if DEFINED(ADC_N(CHANNEL_VBG_ID))
            vbg = ADC_N(CHANNEL_VBG_ID),
        #endif

        #if DEFINED(ADC_N(CHANNEL_GND_ID))
            gnd = ADC_N(CHANNEL_GND_ID),
        #endif
    };

    #if DEFINED(ADC_N(PRESCALER_BIT_0_BIT))
        /// #### enum Prescaler
        /// * div2
        /// * div4
        /// * div8
        /// * div16
        /// * div32
        /// * div64
        /// * div128
        enum class Prescaler : uint8_t {
            #if DEFINED(ADC_N(PRESCALER_2_ID))
                div2 = ADC_N(PRESCALER_2_ID),
            #endif
            #if DEFINED(ADC_N(PRESCALER_4_ID))
                div4 = ADC_N(PRESCALER_4_ID),
            #endif
            #if DEFINED(ADC_N(PRESCALER_8_ID))
                div8 = ADC_N(PRESCALER_8_ID),
            #endif
            #if DEFINED(ADC_N(PRESCALER_16_ID))
                div16 = ADC_N(PRESCALER_16_ID),
            #endif
            #if DEFINED(ADC_N(PRESCALER_32_ID))
                div32 = ADC_N(PRESCALER_32_ID),
            #endif
            #if DEFINED(ADC_N(PRESCALER_64_ID))
                div64 = ADC_N(PRESCALER_64_ID),
            #endif
            #if DEFINED(ADC_N(PRESCALER_128_ID))
                div128 = ADC_N(PRESCALER_128_ID),
            #endif
        };
    #endif

    #if DEFINED(ADC_N(TRIGGER_BIT_0_BIT))
        /// #### enum Trigger
        /// * singleConversion
        /// * freeRunning
        /// * analogComparator
        /// * externalInt0
        /// * timer0CompareMatchA
        /// * timer0Overflow
        /// * timer1CompareMatchB
        /// * timer1Overflow
        /// * timer1CaptureEvent
        /// * freeRunning
        enum class Trigger : uint8_t {
            #if DEFINED(ADC_N(TRIGGER_SINGLE_CONVERSION_ID))
                singleConversion = ADC_N(TRIGGER_SINGLE_CONVERSION_ID),
            #endif
            #if DEFINED(ADC_N(TRIGGER_FREE_RUNNING_ID))
                freeRunning = ADC_N(TRIGGER_FREE_RUNNING_ID),
            #endif
            #if DEFINED(ADC_N(TRIGGER_ANALOG_COMPARATOR_ID))
                analogComparator = ADC_N(TRIGGER_ANALOG_COMPARATOR_ID),
            #endif
            #if DEFINED(ADC_N(TRIGGER_EXTERNAL_INT_0_ID))
                externalInt0 = ADC_N(TRIGGER_EXTERNAL_INT_0_ID),
            #endif
            #if DEFINED(ADC_N(TRIGGER_TIMER0_COMPARE_MATCH_A_ID))
                timer0CompareMatchA = ADC_N(TRIGGER_TIMER0_COMPARE_MATCH_A_ID),
            #endif
            #if DEFINED(ADC_N(TRIGGER_TIMER0_OVERFLOW_ID))
                timer0Overflow = ADC_N(TRIGGER_TIMER0_OVERFLOW_ID),
            #endif
            #if DEFINED(ADC_N(TRIGGER_TIMER1_COMPARE_MATCH_B_ID))
                timer1CompareMatchB = ADC_N(TRIGGER_TIMER1_COMPARE_MATCH_B_ID),
            #endif
            #if DEFINED(ADC_N(TRIGGER_TIMER1_OVERFLOW_ID))
                timer1Overflow = ADC_N(TRIGGER_TIMER1_OVERFLOW_ID),
            #endif
            #if DEFINED(ADC_N(TRIGGER_TIMER1_CAPTURE_EVENT_ID))
                timer1CaptureEvent = ADC_N(TRIGGER_TIMER1_CAPTURE_EVENT_ID),
            #endif
        };
    #endif

    /// #### static constexpr HardwareType getHardwareType()
    /// Get the type of hardware that this class represents.
    static constexpr HardwareType getHardwareType() {
        return HardwareType::adc;
    }

    #if DEFINED(ADC_N(ENABLE_BIT_0_BIT))
        /// #### static void enable(bool e)
        /// Enable/disable the analog to digital converter.
        static force_inline void enable(bool e) {
            setBit_(REG(ADC_N(ENABLE_BIT_0_REG)), ADC_N(ENABLE_BIT_0_BIT), e);
        }
    #endif

    #if DEFINED(ADC_N(START_BIT_0_BIT))
        /// #### static void start()
        /// Start a convertion if set to single conversion or free running modes.
        static force_inline void start() {
            setBit_(REG(ADC_N(START_BIT_0_REG)), ADC_N(START_BIT_0_BIT), true);
        }
    #endif

    #if REG_DEFINED(ADC_N(DATA_REG))
        /// #### static uint16_t value()
        /// Get the the most recent conversion.
        static force_inline uint16_t value() {
            return *REG(ADC_N(DATA_REG));
        }
    #endif

    #if DEFINED(ADC_N(REFERENCE_BIT_0_BIT))
        /// #### static void reference(Reference r)
        /// Set the reference voltage source.
        static force_inline void reference(Reference r) {
            setBit_(REG(ADC_N(REFERENCE_BIT_0_REG)), ADC_N(REFERENCE_BIT_0_BIT), uint8_t(r) & 0x01);
            setBit_(REG(ADC_N(REFERENCE_BIT_1_REG)), ADC_N(REFERENCE_BIT_1_BIT), uint8_t(r) & 0x02);
        }
    #endif

    #if DEFINED(ADC_N(CHANNEL_BIT_0_BIT))
        /// #### static void channel(Channel c)
        /// Set the input channel.
        static force_inline void channel(Channel c) {
            setBit_(REG(ADC_N(CHANNEL_BIT_0_REG)), ADC_N(CHANNEL_BIT_0_BIT), uint8_t(c) & 0x01);
            setBit_(REG(ADC_N(CHANNEL_BIT_1_REG)), ADC_N(CHANNEL_BIT_1_BIT), uint8_t(c) & 0x02);
            setBit_(REG(ADC_N(CHANNEL_BIT_2_REG)), ADC_N(CHANNEL_BIT_2_BIT), uint8_t(c) & 0x04);
            setBit_(REG(ADC_N(CHANNEL_BIT_3_REG)), ADC_N(CHANNEL_BIT_3_BIT), uint8_t(c) & 0x08);
        }
    #endif

    #if DEFINED(ADC_N(PRESCALER_BIT_0_BIT))
        /// #### static void prescaler(Prescaler p)
        /// Set the clock prescaler.
        static force_inline void prescaler(Prescaler p) {
            setBit_(REG(ADC_N(PRESCALER_BIT_0_REG)), ADC_N(PRESCALER_BIT_0_BIT), uint8_t(p) & 0x01);
            setBit_(REG(ADC_N(PRESCALER_BIT_1_REG)), ADC_N(PRESCALER_BIT_1_BIT), uint8_t(p) & 0x02);
            setBit_(REG(ADC_N(PRESCALER_BIT_2_REG)), ADC_N(PRESCALER_BIT_2_BIT), uint8_t(p) & 0x04);
        }
    #endif

    #if DEFINED(ADC_N(LEFT_ADJUST_BIT_0_BIT))
        /// #### static void leftAdjust(bool l)
        /// Enable/disable left adjustment of 10 bit data in 16 bit register.
        static force_inline void leftAdjust(bool l) {
            setBit_(REG(ADC_N(LEFT_ADJUST_BIT_0_REG)), ADC_N(LEFT_ADJUST_BIT_0_BIT), l);
        }
    #endif

    #if DEFINED(ADC_N(TRIGGER_BIT_0_BIT))
        /// #### static void trigger(Trigger t)
        /// Set the conversion trigger source.
        static force_inline void trigger(Trigger t) {
            setBit_(REG(ADC_N(TRIGGER_BIT_0_REG)), ADC_N(TRIGGER_BIT_0_BIT), uint8_t(t) & 0x01);

            #if DEFINED(ADC_N(TRIGGER_BIT_1_BIT))
                setBit_(REG(ADC_N(TRIGGER_BIT_1_REG)), ADC_N(TRIGGER_BIT_1_BIT), uint8_t(t) & 0x02);
            #endif

            #if DEFINED(ADC_N(TRIGGER_BIT_2_BIT))
                setBit_(REG(ADC_N(TRIGGER_BIT_2_REG)), ADC_N(TRIGGER_BIT_2_BIT), uint8_t(t) & 0x04);
            #endif

            #if DEFINED(ADC_N(TRIGGER_BIT_3_BIT))
                setBit_(REG(ADC_N(TRIGGER_BIT_3_REG)), ADC_N(TRIGGER_BIT_3_BIT), uint8_t(t) & 0x08);
            #endif
        }
    #endif

    /// #### static void callback(callback_t callback, void\* data)
    /// Set the callback and data for when a conversion is complete.
    static force_inline void callback(callback_t callback, void* data) {
        _ADC_N(Callback) = callback;
        _ADC_N(CallbackData) = data;
    }

    #if DEFINED(ADC_N(INT_ENABLE_BIT_0_BIT))
        /// #### static void intEnable(bool e)
        /// Enable/disable the ADC interrupt.
        static force_inline void intEnable(bool e) {
            setBit_(REG(ADC_N(INT_ENABLE_BIT_0_REG)), ADC_N(INT_ENABLE_BIT_0_BIT), e);
        }
    #endif

    #if DEFINED(ADC_N(INT_FLAG_BIT_0_BIT))
        /// #### static bool intFlag()
        /// Returns true if the interrupt flag is set.
        static force_inline bool intFlag() {
            return *REG(ADC_N(INT_FLAG_BIT_0_REG)) & bv(ADC_N(INT_FLAG_BIT_0_BIT));
        }
    #endif

    #if DEFINED(ADC_N(INT_FLAG_BIT_0_BIT))
        /// #### static void intFlagClear()
        /// Clear the interrupt flag.
        static force_inline void intFlagClear() {
            setBit_(REG(ADC_N(INT_FLAG_BIT_0_REG)), ADC_N(INT_FLAG_BIT_0_BIT), true);
        }
    #endif
};

} // nbos::hw

//------------------------------------------------------------------

    #endif

    #undef N
    #undef AdcN
    #undef ADC_N
    #undef _ADC_N

    #include "adc.hpp"
#else
    #define NBOS_ADC_HPP
#endif


#endif
