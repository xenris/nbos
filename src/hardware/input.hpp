/// # {{Timer Input}}

/// ```c++
/// using Timer = nbos::hw::Timer1;
///
/// uint16_t value = 0;
///
/// const auto f = [](nbos::hw::Pin::Value* value) {
///     *value = Timer::Input::value();
/// };
///
/// atomic([]() {
///     Timer::waveform(Timer::Waveform::normal);
///     Timer::clock(Timer::Clock::Div1);
///     Timer::Input::edge(Timer::Edge::rising);
///     Timer::Input::intEnable(true);
///     Timer::Input::callback((callback_t)f, &value);
/// });
/// ```

/// ## class {{TimerN::Input}}
struct Input {
    /// #### type Pin
    /// The IO pin which relates to this input.
    using Pin = TIMER_N(INPUT_PIN);

    /// #### enum {{TimerN::Edge}}
    /// * rising
    /// * falling
    enum class Edge : uint8_t {
        rising = TIMER_N(INPUT_EDGE_RISING_ID),
        falling = TIMER_N(INPUT_EDGE_FALLING_ID),
    };

    /// #### static void value(T v)
    static force_inline void value(REGTYPE(TIMER_N(INPUT_REG)) v) {
        *REG(TIMER_N(INPUT_REG)) = v;
    }

    /// #### static T value()
    static force_inline REGTYPE(TIMER_N(INPUT_REG)) value() {
        return *REG(TIMER_N(INPUT_REG));
    }

    /// #### static void edge([[TimerN::Edge]] e)
    static force_inline void edge(Edge e) {
        setBit_(REG(TIMER_N(INPUT_EDGE_SELECT_REG)), TIMER_N(INPUT_EDGE_SELECT_BIT), uint8_t(e) & 0x01);
    }

    /// #### static void callback([[callback_t]] callback, void\* data)
    static force_inline void callback(callback_t callback = nullptr, void* data = nullptr) {
        static callback_t f = nullptr;
        static void* d = nullptr;

        if(callback == nullptr) {
            if(f != nullptr) {
                f(d);
            }
        } else {
            f = callback;
            d = data;
        }
    }

    /// #### static void intEnable(bool b)
    static force_inline void intEnable(bool b) {
        if(b) {
            *REG(TIMER_N(INPUT_INT_ENABLE_REG)) |= bv(TIMER_N(INPUT_INT_ENABLE_BIT));
        } else {
            *REG(TIMER_N(INPUT_INT_ENABLE_REG)) &= ~bv(TIMER_N(INPUT_INT_ENABLE_BIT));
        }
    }

    static force_inline bool intEnabled() {
        return *REG(TIMER_N(INPUT_INT_ENABLE_REG)) & bv(TIMER_N(INPUT_INT_ENABLE_BIT));
    }

    /// #### static bool intFlag()
    static force_inline bool intFlag() {
        return *REG(TIMER_N(INPUT_INT_FLAG_REG)) & bv(TIMER_N(INPUT_INT_FLAG_BIT));
    }

    /// #### static void intFlagClear()
    static force_inline void intFlagClear() {
        *REG(TIMER_N(INPUT_INT_FLAG_REG)) |= bv(TIMER_N(INPUT_INT_FLAG_BIT));
    }
};
