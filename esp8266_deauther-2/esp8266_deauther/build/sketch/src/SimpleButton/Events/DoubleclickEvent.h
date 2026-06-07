#line 1 "D:\\Arduino\\esp8266_deauther-2\\esp8266_deauther\\src\\SimpleButton\\Events\\DoubleclickEvent.h"
#ifndef SimpleButton_DoubleclickEvent_h
#define SimpleButton_DoubleclickEvent_h

#include "Event.h"

namespace simplebutton {
    class DoubleclickEvent : public Event {
        public:
            DoubleclickEvent(ButtonEventFunction, uint32_t minPushTime, uint32_t minReleaseTime, uint32_t timeSpan);
            ~DoubleclickEvent();

            uint8_t getMode();
            uint32_t getMinPushTime();
            uint32_t getMinReleaseTime();
            uint32_t getTimeSpan();

        private:
            uint32_t minPushTime    = 0;
            uint32_t minReleaseTime = 0;
            uint32_t timeSpan       = 0;
    };
}

#endif // ifndef SimpleButton_DoubleclickEvent_h