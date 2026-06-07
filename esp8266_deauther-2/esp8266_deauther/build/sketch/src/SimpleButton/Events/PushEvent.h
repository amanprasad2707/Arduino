#line 1 "D:\\Arduino\\esp8266_deauther-2\\esp8266_deauther\\src\\SimpleButton\\Events\\PushEvent.h"
#ifndef SimpleButton_PushEvent_h
#define SimpleButton_PushEvent_h

#include "Event.h"

namespace simplebutton {
    class PushEvent : public Event {
        public:
            PushEvent(ButtonEventFunction);
            ~PushEvent();

            uint8_t getMode();
    };
}

#endif // ifndef SimpleButton_PushEvent_h