#define ExIntN CONCAT(ExInt, ID, )

#define ENABLE_REG CONCAT(CHIP_EXINT_, ID, _ENABLE_REG)
#define TRIGGER_BIT_0_REG CONCAT(CHIP_EXINT_, ID, _TRIGGER_BIT_0_REG)
#define TRIGGER_BIT_1_REG CONCAT(CHIP_EXINT_, ID, _TRIGGER_BIT_1_REG)
#define FLAG_REG CONCAT(CHIP_EXINT_, ID, _FLAG_REG)

#define ENABLE_BIT CONCAT(CHIP_EXINT_, ID, _ENABLE_BIT)
#define TRIGGER_BIT_0_BIT CONCAT(CHIP_EXINT_, ID, _TRIGGER_BIT_0_BIT)
#define TRIGGER_BIT_1_BIT CONCAT(CHIP_EXINT_, ID, _TRIGGER_BIT_1_BIT)
#define FLAG_BIT CONCAT(CHIP_EXINT_, ID, _FLAG_BIT)

#define TRIGGER_LOW_ID CONCAT(CHIP_EXINT_, N, _TRIGGER_LOW_ID)
#define TRIGGER_CHANGE_ID CONCAT(CHIP_EXINT_, N, _TRIGGER_CHANGE_ID)
#define TRIGGER_FALLING_ID CONCAT(CHIP_EXINT_, N, _TRIGGER_FALLING_ID)
#define TRIGGER_RISING_ID CONCAT(CHIP_EXINT_, N, _TRIGGER_RISING_ID)

#define INTERRUPT CONCAT(_exInt, ID, Interrupt)
#define INTERRUPT_DATA CONCAT(_exInt, ID, InterruptData)

struct ExIntN {
    ExIntN() = delete;

    static constexpr HardwareType getHardwareType() {
        return HardwareType::ExInt;
    }

    enum class Trigger : uint8_t {
        Low = TRIGGER_LOW_ID,
        Change = TRIGGER_CHANGE_ID,
        Falling = TRIGGER_FALLING_ID,
        Rising = TRIGGER_RISING_ID,
    };

    static force_inline void enable(Trigger trigger, void (*interrupt)(void*), void* data) {
        // Register interrupt function.
        INTERRUPT = interrupt;
        INTERRUPT_DATA = data;

        // Configure trigger.
        setBit_(TRIGGER_BIT_0_REG, TRIGGER_BIT_0_BIT, (uint8_t)trigger & 0x01);
        setBit_(TRIGGER_BIT_1_REG, TRIGGER_BIT_1_BIT, (uint8_t)trigger & 0x02);

        // Enable interrupt.
        setBit_(ENABLE_REG, ENABLE_BIT, true);

        // Clear interrupt flag.
        setBit_(FLAG_REG, FLAG_BIT, true);
    }

    static force_inline void disable() {
        // Unregister interrupt function.
        INTERRUPT = nullptr;
        INTERRUPT_DATA = nullptr;

        // Disable interrupt.
        setBit(ENABLE_REG, ENABLE_BIT, false);

        // Clear interrupt flag.
        setBit(FLAG_REG, FLAG_BIT, true);
    }
};

#undef ExIntN

#undef ENABLE_REG
#undef TRIGGER_BIT_0_REG
#undef TRIGGER_BIT_1_REG
#undef FLAG_REG

#undef ENABLE_BIT
#undef TRIGGER_BIT_0_BIT
#undef TRIGGER_BIT_1_BIT
#undef FLAG_BIT

#undef TRIGGER_LOW_ID
#undef TRIGGER_CHANGE_ID
#undef TRIGGER_FALLING_ID
#undef TRIGGER_RISING_ID

#undef INTERRUPT
#undef INTERRUPT_DATA
