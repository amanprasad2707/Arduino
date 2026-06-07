#line 1 "D:\\Arduino\\esp8266_deauther-2\\esp8266_deauther\\src\\SimpleButton\\Events\\ReleaseEvent.cpp"
#include "ReleaseEvent.h"

namespace simplebutton {
    ReleaseEvent::ReleaseEvent(ButtonEventFunction) {
        this->fnct = fnct;
    }

    ReleaseEvent::~ReleaseEvent() {
        if (next) {
            delete next;
            next = NULL;
        }
    }

    uint8_t ReleaseEvent::getMode() {
        return MODE::RELEASED;
    }
}