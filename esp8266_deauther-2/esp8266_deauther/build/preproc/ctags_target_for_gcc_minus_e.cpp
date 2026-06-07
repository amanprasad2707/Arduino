# 1 "D:\\Arduino\\esp8266_deauther-2\\esp8266_deauther\\esp8266_deauther.ino"
/* =====================
   This software is licensed under the MIT License:
   https://github.com/spacehuhntech/esp8266_deauther
   ===================== */

extern "C" {
    // Please follow this tutorial:
    // https://github.com/spacehuhn/esp8266_deauther/wiki/Installation#compiling-using-arduino-ide
    // And be sure to have the right board selected
# 11 "D:\\Arduino\\esp8266_deauther-2\\esp8266_deauther\\esp8266_deauther.ino" 2
}

# 14 "D:\\Arduino\\esp8266_deauther-2\\esp8266_deauther\\esp8266_deauther.ino" 2

# 16 "D:\\Arduino\\esp8266_deauther-2\\esp8266_deauther\\esp8266_deauther.ino" 2







# 24 "D:\\Arduino\\esp8266_deauther-2\\esp8266_deauther\\esp8266_deauther.ino" 2
# 25 "D:\\Arduino\\esp8266_deauther-2\\esp8266_deauther\\esp8266_deauther.ino" 2
# 26 "D:\\Arduino\\esp8266_deauther-2\\esp8266_deauther\\esp8266_deauther.ino" 2
# 27 "D:\\Arduino\\esp8266_deauther-2\\esp8266_deauther\\esp8266_deauther.ino" 2
# 28 "D:\\Arduino\\esp8266_deauther-2\\esp8266_deauther\\esp8266_deauther.ino" 2
# 29 "D:\\Arduino\\esp8266_deauther-2\\esp8266_deauther\\esp8266_deauther.ino" 2
# 30 "D:\\Arduino\\esp8266_deauther-2\\esp8266_deauther\\esp8266_deauther.ino" 2
# 31 "D:\\Arduino\\esp8266_deauther-2\\esp8266_deauther\\esp8266_deauther.ino" 2
# 32 "D:\\Arduino\\esp8266_deauther-2\\esp8266_deauther\\esp8266_deauther.ino" 2





// Run-Time Variables //
Names names;
SSIDs ssids;
Accesspoints accesspoints;
Stations stations;
Scan scan;
Attack attack;
CLI cli;
DisplayUI displayUI;

simplebutton::Button* resetButton;

# 50 "D:\\Arduino\\esp8266_deauther-2\\esp8266_deauther\\esp8266_deauther.ino" 2

uint32_t autosaveTime = 0;
uint32_t currentTime = 0;

bool booted = false;

void setup() {
    // for random generator
    randomSeed(os_random());

    // start serial
    Serial.begin(115200);
    Serial.println();

    // start SPIFFS
    prnt(SETUP_MOUNT_SPIFFS);
    // bool spiffsError = !LittleFS.begin();
    LittleFS.begin();
    prntln(/*spiffsError ? SETUP_ERROR : */ SETUP_OK);

    // Start EEPROM
    EEPROMHelper::begin(4095);
# 85 "D:\\Arduino\\esp8266_deauther-2\\esp8266_deauther\\esp8266_deauther.ino"
    // Format SPIFFS when in boot-loop
    if (/*spiffsError || */ !EEPROMHelper::checkBootNum(1)) {
        prnt(SETUP_FORMAT_SPIFFS);
        LittleFS.format();
        prntln(SETUP_OK);

        prnt(SETUP_FORMAT_EEPROM);
        EEPROMHelper::format(4095);
        prntln(SETUP_OK);

        EEPROMHelper::resetBootNum(1);
    }

    // get time
    currentTime = millis();

    // load settings

    settings::load();





    wifi::begin();
    wifi_set_promiscuous_rx_cb([](uint8_t* buf, uint16_t len) {
        scan.sniffer(buf, len);
    });

    // start display
    if (settings::getDisplaySettings().enabled) {
        displayUI.setup();
        displayUI.mode = DISPLAY_MODE::INTRO;
    }

    // load everything else
    names.load();
    ssids.load();
    cli.load();

    // create scan.json
    scan.setup();

    // dis/enable serial command interface
    if (settings::getCLISettings().enabled) {
        cli.enable();
    } else {
        prntln(SETUP_SERIAL_WARNING);
        Serial.flush();
        Serial.end();
    }

    // start access point/web interface
    if (settings::getWebSettings().enabled) wifi::startAP();

    // STARTED
    prntln(SETUP_STARTED);

    // version
    prntln("2.6.1");

    // setup LED
    led::setup();

    // setup reset button
    resetButton = new ButtonPullup(0);
}

void loop() {
    currentTime = millis();

    led::update(); // update LED color
    wifi::update(); // manage access point
    attack.update(); // run attacks
    displayUI.update();
    cli.update(); // read and run serial input
    scan.update(); // run scan
    ssids.update(); // run random mode, if enabled

    // auto-save
    if (settings::getAutosaveSettings().enabled
        && (currentTime - autosaveTime > settings::getAutosaveSettings().time)) {
        autosaveTime = currentTime;
        names.save(false);
        ssids.save(false);
        settings::save(false);
    }

    if (!booted) {
        booted = true;
        EEPROMHelper::resetBootNum(1);



    }

    resetButton->update();
    if (resetButton->holding(5000)) {
        led::setMode(LED_MODE::SCAN);
        DISPLAY_MODE _mode = displayUI.mode;
        displayUI.mode = DISPLAY_MODE::RESETTING;
        displayUI.update(true);

        settings::reset();
        settings::save(true);

        delay(2000);

        led::setMode(LED_MODE::IDLE);
        displayUI.mode = _mode;
    }
}
