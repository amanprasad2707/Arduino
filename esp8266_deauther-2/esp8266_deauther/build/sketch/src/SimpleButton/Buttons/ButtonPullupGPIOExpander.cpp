#line 1 "D:\\Arduino\\esp8266_deauther-2\\esp8266_deauther\\src\\SimpleButton\\Buttons\\ButtonPullupGPIOExpander.cpp"
#include "ButtonPullupGPIOExpander.h"

namespace simplebutton {
    ButtonPullupGPIOExpander::ButtonPullupGPIOExpander() {
        setup(NULL, 255);
    }

    ButtonPullupGPIOExpander::ButtonPullupGPIOExpander(GPIOExpander* pcf, uint8_t pin) {
        setup(pcf, pin);
    }

    ButtonPullupGPIOExpander::~ButtonPullupGPIOExpander() {}

    void ButtonPullupGPIOExpander::setup(GPIOExpander* pcf, uint8_t pin) {
        this->pcf             = pcf;
        this->button_pin      = pin;
        this->button_inverted = true;
        enable();
    }

    void ButtonPullupGPIOExpander::enable() {
        button_enabled = true;

        if (pcf) {
            pcf->write(button_pin, 1);
            if (pcf->connected()) button_setup = true;
        }
    }
}
