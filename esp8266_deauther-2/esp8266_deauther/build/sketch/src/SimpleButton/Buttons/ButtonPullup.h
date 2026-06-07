#line 1 "D:\\Arduino\\esp8266_deauther-2\\esp8266_deauther\\src\\SimpleButton\\Buttons\\ButtonPullup.h"
#ifndef SimpleButton_ButtonPullup_h
#define SimpleButton_ButtonPullup_h

#include "Button.h"

namespace simplebutton {
    class ButtonPullup : public Button {
        public:
            ButtonPullup();
            ButtonPullup(uint8_t pin);

            ~ButtonPullup();

            void setup(uint8_t pin);

            void enable();
    };
}

#endif // ifndef SimpleButton_ButtonPullup_h