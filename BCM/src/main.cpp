#include <Arduino.h>

#define LED_OFF HIGH
#define LED_ON LOW

template <size_t N>
class BCMDisplay{
public:
    static constexpr const
    size_t resolution = 8;
    static_assert(0 < resolution && resolution <= 8);

    static constexpr const
    unsigned long period = 10240; // microseconds
    static_assert(period > 0 && period % (1UL << (resolution + 1)) == 0);

private:
    using Buffer = bool[resolution][N];

public:
    BCMDisplay(const uint8_t (&pins)[N])
        : pins{ pins }
    { }

    void begin() {
        for (auto pin: pins) {
            pinMode(pin, OUTPUT);
            digitalWrite(pin, LED_OFF);
        }
    }

    void setBright(size_t nth, uint8_t bright) {
        auto& buf = getBackBuffer();
        bright >>= (8 - resolution);
        for (size_t i = 0; i < resolution; ++i) {
            buf[i][nth] = bright & 1;
            bright >>= 1;
        }
    }

    uint8_t getBright(size_t nth) const {
        auto& buf = getBackBuffer();
        uint8_t bright{};

        for (size_t i = 0; i < resolution; ++i) {
            bright |= (buf[i][nth] & 1) << i;
        }

        return bright << (8 - resolution);
    }

    void update() {
        update_flag = true;
    }

    size_t displaySize() const {
        return N;
    }

    void loop() {
        refresh();
    }

private:
    Buffer& getFrontBuffer() {
        return buffer[front_buf_pointer];
    }
    const Buffer& getFrontBuffer() const {
        return buffer[front_buf_pointer];
    }

    Buffer& getBackBuffer() {
        return buffer[front_buf_pointer ^ 1];
    }
    const Buffer& getBackBuffer() const {
        return buffer[front_buf_pointer ^ 1];
    }

    void refresh() {
        auto curr_us = micros();
        if (curr_us - prev_us < curr_period) return;
        prev_us += curr_us;
        
        change_output();

        if (!--res_cnt) {
            curr_period = period;
            res_cnt = resolution;
            if (update_flag) {
                updateBuffer();
                update_flag = false;
            }
        }
        curr_period >>= 1;
    }

    void change_output() {
        auto& curr_buf = getFrontBuffer()[res_cnt - 1];
        for(size_t i = 0; i < N; ++i) {
            digitalWrite(pins[i], curr_buf[i] == LED_ON);
        }
    }

    void all_off() {
        for(size_t i = 0; i < N; ++i) {
            digitalWrite(pins[i], LED_OFF);
        }
    }

    void updateBuffer() {
        swapBuffer();
        copyFrontToBackBuffer();
    }

    void copyFrontToBackBuffer() {
        auto& fbuf = getFrontBuffer();
        auto& bbuf = getBackBuffer();

        memcpy(bbuf, fbuf, sizeof(bbuf));
    }

    void swapBuffer() {
        front_buf_pointer ^= 1;
    }

private:
    const uint8_t (&pins)[N];
    unsigned long prev_us;
    unsigned long curr_period;
    size_t res_cnt = resolution;
    Buffer buffer[2];
    uint8_t front_buf_pointer;
    bool update_flag = false;
};

static inline
void change_bright();

static constexpr const uint8_t pins[]{ 4, 5, 6, 7 };
static BCMDisplay<sizeof(pins)> display(pins);

void setup() {
    Serial.begin(9600);
    display.begin();

//    for (size_t i = 0; i < display.displaySize(); ++i) {
//        display.setBright(i, 256 * i / 5);
//    }
}

void loop() {
    static unsigned long prev_ms;

    display.loop();

    auto curr_ms = millis();
    if (curr_ms - prev_ms >= 100) {
        prev_ms = curr_ms;
        change_bright();
    }
}

static inline
void change_bright() {
//    for (size_t i = 0; i < display.displaySize(); ++i) {
//        display.setBright(i, (display.getBright(i) + (1 << (8 - display.resolution))) % 256);
//    }
//    display.update();

    static uint8_t bright = 0;
    for (size_t i = 0; i < display.displaySize(); ++i) {
        display.setBright(i, bright << (8 - display.resolution));
    }
    display.update();

    bright = (bright + 1) % (1 << display.resolution);

//    Serial.print("bright: ");
//    Serial.println(bright);
}
