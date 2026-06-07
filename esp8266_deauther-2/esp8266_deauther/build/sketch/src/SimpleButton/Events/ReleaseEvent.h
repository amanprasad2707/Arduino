#line 1 "D:\\Arduino\\esp8266_deauther-2\\esp8266_deauther\\src\\SimpleButton\\Events\\ReleaseEvent.h"
#ifndef SimpleButton_ReleaseEvent_h
#define SimpleButton_ReleaseEvent_h

#include "Event.h"

namespace simplebutton {
    class ReleaseEvent : public Event {
        public:
            ReleaseEvent(ButtonEventFunction);
            ~ReleaseEvent();

            uint8_t getMode();
    };
}

#endif // ifndef SimpleButton_ReleaseEvent_h