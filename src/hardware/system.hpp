/// [[Index]]

/// # {{System}}

#ifndef NBLIB_SYSTEM_HPP
#define NBLIB_SYSTEM_HPP

#include "chip.hpp"
#include "../macros.hpp"
#include "../primitive.hpp"

#ifndef SANITISE_REG_FOR_TEST
    #define SANITISE_REG_FOR_TEST(REG)
#endif

/// ### atomic\(expr\)
/// Disables interrupts while accessing/evaluating "expr".<br>
/// Required when accessing variables which are shared with interrupt callbacks. e.g.
/// ```c++
/// int localVariable = atomic(globalVariable);
/// // Or
/// int localVariable = atomic(globalVariable, 0);
/// // to get and set the value atomically.
/// ```

/// ### atomic\(\) \{expr1; expr2; expr3; etc...\}
/// Disables interrupts while running a block of code.

#ifdef __clang__
    #define atomic(...) __VA_ARGS__
#else
    #define atomic(...) CAT(atomic_, LENGTH(__VA_ARGS__))(__VA_ARGS__)
    #define atomic_0() if(nblib::__Atomic __a; true)
    #define atomic_1(A) (nblib::__Atomic(), A)
    #define atomic_2(A, B) (nblib::__Atomic(), nblib::__getThenSet(A, B))
#endif

/// ### non_atomic\(expr\)
/// Inverse of atomic.

/// ### non_atomic\(\) \{expr1; expr2; expr3; etc...\}
/// Inverse of atomic.

#ifdef __clang__
    #define non_atomic(...) __VA_ARGS__
#else
    #define non_atomic(...) CAT(non_atomic_, LENGTH(__VA_ARGS__))(__VA_ARGS__)
    #define non_atomic_0() if(nblib::__NonAtomic __n; true)
    #define non_atomic_1(A) (nblib::__NonAtomic(), A)
    #define non_atomic_2(A, B) (nblib::__NonAtomic(), nblib::__getThenSet(A, B))
#endif
/// ### block\(expr\)
/// Prevents the expression from being optimised into the code around it. e.g.
/// ```c++
/// LedPin::output(LedPin::Value::high);
/// LedPin::output(LedPin::Value::low);
/// ```
/// will only set the pin low, because the compiler saw that this was the overall effect of the expressions. Whereas:
/// ```c++
/// block(LedPin::output(LedPin::Value::high));
/// block(LedPin::output(LedPin::Value::low));
/// ```
/// will set the pin high, then low:

/// ### block\(\) \{expr1; expr2; expr3; etc...\}
/// Same as block(expr), but allows several expressions to be optimised together, separate to any code around it.
#ifdef __clang__
    #define block(...) __VA_ARGS__
#else
    #define block(...) CAT(block_, LENGTH(__VA_ARGS__))(__VA_ARGS__)
    #define block_0() if(nblib::__Block __b; true)
    #define block_1(A) (nblib::__Block(), A)
    #define block_2(A, B) (nblib::__Block(), nblib::__getThenSet(A, B))
#endif

namespace nblib {

template <class T>
T __getThenSet(T& a, const T& b) {
    const T t = a;
    a = b;
    return t;
}

struct __Block {
    __Block() {
        asm volatile("" ::: "memory");
    }

    ~__Block() {
        asm volatile("" ::: "memory");
    }
};

/// #### T bv(int n)
/// Equivalent to "1 << n".
template <class T>
force_inline T bv(int n) {
    static_assert(isInteger<T>(), "bv requires an integer");

    return T(T(1) << T(n));
}

/// #### void setBit(T\* register, uint8_t bit, bool value)
/// Set or clear a bit in a register immediately.

/// #### void setBit_(T\* register, uint8_t bit, bool value)
/// Set or clear a bit in a register lazily.
/// (i.e. Allow compiler to rearrange and combine instructions for faster code.)

template <class T>
force_inline void setBit_(T* reg, uint8_t bit, bool value) {
    static_assert(!isSigned<T>(), "setBit requires a pointer to an unsigned integer");

    SANITISE_REG_FOR_TEST(reg);

    if(value) {
        *reg = T(*reg | bv<T>(T(bit)));
    } else {
        *reg = T(*reg & ~bv<T>(T(bit)));
    }
}

template <class T>
force_inline void setBit_(T* reg, T mask, uint8_t bit, bool value) {
    static_assert(!isSigned<T>(), "setBit requires a pointer to an unsigned integer");

    SANITISE_REG_FOR_TEST(reg);

    if(value) {
        *reg = T(mask & (*reg | bv<T>(T(bit))));
    } else {
        *reg = T(mask & (*reg & ~bv<T>(T(bit))));
    }
}

template <class T>
force_inline void setBit(T* reg, uint8_t bit, bool value) {
    block() {
        setBit_(reg, bit, value);
    }
}

/// #### void getBit(T\* register, uint8_t bit)
/// Get a bit in a register immediately.

/// #### void getBit_(T\* register, uint8_t bit)
/// Get a bit in a register lazily.
/// (i.e. Allow compiler to rearrange and combine instructions for faster code.)

template <class T>
force_inline bool getBit_(T* reg, uint8_t bit) {
    static_assert(!isSigned<T>(), "getBit requires a pointer to an unsigned integer");

    SANITISE_REG_FOR_TEST(reg);

    return bool(*reg & bv<T>(T(bit)));
}

template <class T>
force_inline bool getBit(T* reg, uint8_t bit) {
    block() {
        return getBit_(reg, bit);
    }
}

/// #### void clearFlagBit(T\* register, uint8_t bit)
/// Clear a flag bit in a flag register.
template <class T>
force_inline void clearFlagBit(T* reg, uint8_t bit) {
    static_assert(!isSigned<T>(), "clearFlagBit requires a pointer to an unsigned integer");

    SANITISE_REG_FOR_TEST(reg);

    *reg = bv<T>(T(bit));
}

/// #### void setReg(T\* register, T value)
/// Set the value of a register immediately.

/// #### void setReg_(T\* register, T value)
/// Set the value of a register lazily.
/// (i.e. Allow compiler to rearrange and combine instructions for faster code.)

template <class T>
force_inline void setReg_(T* reg, T value) {
    static_assert(!isSigned<T>(), "setReg requires a pointer to an unsigned integer");

    SANITISE_REG_FOR_TEST(reg);

    *reg = value;
}

template <class T>
force_inline void setReg(T* reg, T value) {
    block() {
        setReg_(reg, value);
    }
}

/// #### void getReg(T\* register)
/// Get the value of a register immediately.

/// #### void getReg_(T\* register)
/// Get the value of a register lazily.
/// (i.e. Allow compiler to rearrange and combine instructions for faster code.)

template <class T>
force_inline T& getReg_(T* reg) {
    static_assert(!isSigned<T>(), "getReg requires a pointer to an unsigned integer");

    SANITISE_REG_FOR_TEST(reg);

    return *reg;
}

template <class T>
force_inline T& getReg(T* reg) {
    block() {
        return getReg_(reg);
    }
}

force_inline void nop() {
    #if defined(__AVR__) || defined(__ARM__)
        asm volatile("nop" ::: "memory");
    #elif defined(TEST)
        // Ignore this function.
    #else
        #warning nop() not defined for this architecture.
    #endif
}

/// #### void delay<uint64_t cpuFreq, uint64_t ns>()
/// Delays the cpu for the given number of nanoseconds.<br>
/// Should only be used for very short delays.<br>
/// Limited to 10 milliseconds.<br>
/// Rounds to the nearest possible delay time. e.g. at 16MHz, delay<50>() will
/// delay for 62.5 nanoseconds (1 cpu clock cycle).<br>
/// Is limited further by faster clock speeds. e.g. at 100MHz it will be limited to 2621434ns.
template <uint64_t cpuFreq, uint64_t ns>
force_inline void delay() {
    static_assert(ns <= 10000000, "Delay limited to 10 milliseconds (10000000 ns)");

    // Ensure that this delay separates hardware actions, even when 0ns.
    block() {}

    constexpr uint64_t clocks = (uint64_t(ns) * cpuFreq + 500000000) / 1000000000;
    constexpr uint64_t clocksPerLoop = 4;

    // TODO Handle higher cpu frequencies.
    static_assert(clocks / 4 <= uint64_t(max<uint16_t>()), "Cannot handle this length of delay at this cpu frequency");

    constexpr uint16_t loops = uint16_t((clocks <= 0) ? (0) : ((clocks - 1) / clocksPerLoop));
    constexpr uint16_t nops = uint16_t((clocks <= 4) ? (clocks) : ((clocks - 1) % clocksPerLoop));

    #if defined(__AVR__)
        if constexpr (loops != 0) {
            const uint16_t c = loops;

            asm volatile (
                "ldi r30, %0\n"
                "ldi r31, %1\n"
                "1: sbiw r30, 1\n"
                "brne 1b\n"
                :
                : "" (uint8_t(c)), "" (uint8_t(c >> 8))
                : "r30", "r31"
            );
        }
    #elif defined(__ARM__)

    #elif defined(TEST)
        (void)loops;
    #else

    #endif


    if constexpr (nops == 1) {
        nop();
    } else if constexpr (nops == 2) {
        nop(); nop();
    } else if constexpr (nops == 3) {
        nop(); nop(); nop();
    } else if constexpr (nops == 4) {
        nop(); nop(); nop(); nop();
    }
}

// TODO Check that these functions work for arm.

/// #### void interruptsEnable(bool)
/// Enable/disable interrupts.
force_inline void interruptsEnable(bool enable) {
    #if defined(__AVR__)
        if(enable) {
            asm volatile("sei" ::: "memory");
        } else {
            asm volatile("cli" ::: "memory");
        }
    #elif defined(__ARM__)
        if(enable) {
            asm volatile("cpsie i" ::: "memory");
        } else {
            asm volatile("cpsid i" ::: "memory");
        }
    #elif defined(TEST)
        // Ignore this function.
    #else
        #warning interruptsEnable(bool) not defined for this architecture.
    #endif
}

/// #### bool interruptsEnabled()
/// Returns true if interrupts are enabled.
force_inline bool interruptsEnabled() {
    bool t = false;

    #if defined(__AVR__)
        t = getBit(REG(CHIP_SYSTEM_GLOBAL_INTERRUPT_BIT_0_REG), CHIP_SYSTEM_GLOBAL_INTERRUPT_BIT_0_BIT);
    #elif defined(__ARM__)
        asm volatile("mrs %[t], PRIMASK" : [t] "=r" (t) :: "memory");
    #elif defined(TEST)
        // Ignore this function.
    #else
        #warning interruptsEnabled() not defined for this architecture.
    #endif

    return t;
}

struct __Atomic {
    bool _i;

    force_inline __Atomic() {
        block() {
            _i = nblib::interruptsEnabled();

            nblib::interruptsEnable(false);
        }
    }

    force_inline ~__Atomic() {
        block() {
            if(_i) {
                nblib::interruptsEnable(true);
            }
        }
    }
};

struct __NonAtomic {
    bool _i;

    __NonAtomic() {
        block() {
            _i = nblib::interruptsEnabled();

            nblib::interruptsEnable(true);
        };
    }

    ~__NonAtomic() {
        block() {
            if(!_i) {
                nblib::interruptsEnable(false);
            }
        }
    }
};

#define SYSTEM(A) CAT(CHIP_SYSTEM_, A)

struct System {
    System() = delete;
    System& operator=(const System&) = delete;
    System(const System&) = delete;

    #if REG_ADDR(SYSTEM(ALLOW_CONFIG_CHANGE_REG))
        /// #### enum {{System::ConfigChangeProtection}}
        /// * selfProgram
        /// * ioReg
        enum class ConfigChangeProtection {
            #if DEFINED(SYSTEM(ALLOW_CONFIG_CHANGE_SELF_PROGRAM_ID))
                selfProgram = SYSTEM(ALLOW_CONFIG_CHANGE_SELF_PROGRAM_ID),
            #endif

            #if DEFINED(SYSTEM(ALLOW_CONFIG_CHANGE_IO_REG_ID))
                ioReg = SYSTEM(ALLOW_CONFIG_CHANGE_IO_REG_ID),
            #endif
        };
    #endif

    #if REG_ADDR(SYSTEM(ALLOW_CONFIG_CHANGE_REG))
        /// #### static void allowConfigChange([[System::ConfigChangeProtection]])
        static force_inline void allowConfigChange(ConfigChangeProtection c) {
            using T = REG_TYPE(SYSTEM(ALLOW_CONFIG_CHANGE_REG));

            setBits(REG(SYSTEM(ALLOW_CONFIG_CHANGE_REG)), T(SYSTEM(ALLOW_CONFIG_CHANGE_MASK)), T(c));
        }
    #endif

    #if REG_ADDR(SYSTEM(ALLOW_CONFIG_CHANGE_REG))
        template <class T>
        static force_inline void setBit(T* reg, uint8_t bit, bool value, ConfigChangeProtection c) {
            static_assert(!isSigned<T>(), "setBit requires a pointer to an unsigned integer");

            SANITISE_REG_FOR_TEST(reg);

            block() {
                T r = value ? T(*reg | bv<T>(T(bit))) : T(*reg & ~bv<T>(T(bit)));

                System::allowConfigChange(c);

                *reg = r;
            }
        }
    #endif

    template <class T>
    static force_inline void setBit(T* reg, uint8_t bit, bool value) {
        static_assert(!isSigned<T>(), "setBit requires a pointer to an unsigned integer");

        SANITISE_REG_FOR_TEST(reg);

        *reg = value ? T(*reg | bv<T>(T(bit))) : T(*reg & ~bv<T>(T(bit)));
    }

    #if REG_ADDR(SYSTEM(ALLOW_CONFIG_CHANGE_REG))
        template <class T>
        static force_inline void setBits(T* reg, T mask, T bits, ConfigChangeProtection c) {
            static_assert(!isSigned<T>(), "setBits requires a pointer to an unsigned integer");

            SANITISE_REG_FOR_TEST(reg);

            block() {
                T r = T((*reg & ~mask) | bits);

                System::allowConfigChange(c);

                *reg = r;
            }
        }
    #endif

    template <class T>
    static force_inline void setBits(T* reg, T mask, T bits) {
        static_assert(!isSigned<T>(), "setBits requires a pointer to an unsigned integer");

        SANITISE_REG_FOR_TEST(reg);

        *reg = T((*reg & ~mask) | bits);
    }

    #if REG_ADDR(SYSTEM(ALLOW_CONFIG_CHANGE_REG))
        template <class T>
        static force_inline void setReg(T* reg, T value, ConfigChangeProtection c) {
            static_assert(!isSigned<T>(), "setReg requires a pointer to an unsigned integer");

            SANITISE_REG_FOR_TEST(reg);

            block() {
                System::allowConfigChange(c);

                *reg = value;
            }
        }
    #endif

    template <class T>
    static force_inline void setReg(T* reg, T value) {
        static_assert(!isSigned<T>(), "setReg requires a pointer to an unsigned integer");

        SANITISE_REG_FOR_TEST(reg);

        *reg = value;
    }
};

#undef SYSTEM

}

#endif
