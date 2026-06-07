#line 1 "D:\\Arduino\\esp8266_deauther-2\\esp8266_deauther\\src\\SimpleButton\\Buttons\\ButtonPullupGPIOExpander.h"
#ifndef SimpleButton_ButtonPullupGPIOExpander_h
#define SimpleButton_ButtonPullupGPIOExpander_h

#include "ButtonGPIOExpander.h"

namespace simplebutton {
    class ButtonPullupGPIOExpander : public ButtonGPIOExpander {
        public:
            ButtonPullupGPIOExpander();
            ButtonPullupGPIOExpander(GPIOExpander* pcf, uint8_t pin);

            ~ButtonPullupGPIOExpander();

            void setup(GPIOExpander* pcf, uint8_t pin);

            void enable();
    };
}

#endif // ifndef SimpleButton_ButtonPullupGPIOExpander_h