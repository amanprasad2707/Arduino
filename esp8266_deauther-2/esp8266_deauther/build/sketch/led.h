#line 1 "D:\\Arduino\\esp8266_deauther-2\\esp8266_deauther\\led.h"
/* This software is licensed under the MIT License: https://github.com/spacehuhntech/esp8266_deauther */

#pragma once

#include <cstdint>

enum LED_MODE {
    OFF,
    SCAN,
    ATTACK,
    IDLE
};

namespace led {
    void setup();
    void update();
    void setMode(LED_MODE new_mode, bool force = false);
    void setColor(uint8_t r, uint8_t g, uint8_t b);
}