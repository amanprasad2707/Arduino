// Include BLE Mouse library
#include <BleMouse.h>

// Define RGB LED pins (choose valid ESP32 GPIOs)
#define R_PIN 2   // Red LED
#define G_PIN 4   // Green LED
#define B_PIN 5   // Blue LED

// Define Button pins (choose valid ESP32 GPIOs)
#define U_BUT 12  // Up Button
#define L_BUT 14  // Left Button
#define C_BUT 27  // Center Button
#define R_BUT 26  // Right Button
#define D_BUT 25  // Down Button

// BLE Mouse global declaration
BleMouse bleMouse;
bool isConnected = false;

void setup() {
    Serial.begin(115200);
    Serial.println("Starting BLE Mouse...");

    // Configure LED pins as output
    pinMode(R_PIN, OUTPUT);
    pinMode(G_PIN, OUTPUT);
    pinMode(B_PIN, OUTPUT);

    // Configure Button pins as input with pull-up resistors
    pinMode(U_BUT, INPUT_PULLUP);
    pinMode(L_BUT, INPUT_PULLUP);
    pinMode(C_BUT, INPUT_PULLUP);
    pinMode(R_BUT, INPUT_PULLUP);
    pinMode(D_BUT, INPUT_PULLUP);

    // Start BLE Mouse
    bleMouse.begin();
    Serial.println("BLE Mouse Initialized!");
}

void loop() {
    if (bleMouse.isConnected()) {
        if (!isConnected) {  // Run only once when connected
            Serial.println("BLE Mouse Connected!");
            digitalWrite(G_PIN, HIGH); // Green LED ON
            isConnected = true;
        }
        handleMouseActions();
    } else {
        if (isConnected) {  // Run only once when disconnected
            Serial.println("BLE Mouse Disconnected...");
            isConnected = false;
        }
        blinkRedLED();
    }
}

// Blink Red LED when Bluetooth is not connected
void blinkRedLED() {
    digitalWrite(R_PIN, HIGH);
    delay(500);
    digitalWrite(R_PIN, LOW);
    delay(500);
}

// Flash Blue LED when a button is pressed
void indicateButtonPress() {
    digitalWrite(B_PIN, HIGH);
    delay(100);
    digitalWrite(B_PIN, LOW);
}

// Handle button presses for mouse actions
void handleMouseActions() {
    if (digitalRead(U_BUT) == LOW) {
        bleMouse.move(0, 0, 1);  // Scroll up
        indicateButtonPress();
        Serial.println("Scrolling UP");
        delay(100);
    }

    if (digitalRead(D_BUT) == LOW) {
        bleMouse.move(0, 0, -1);  // Scroll down
        indicateButtonPress();
        Serial.println("Scrolling DOWN");
        delay(100);
    }

    if (digitalRead(C_BUT) == LOW) {
        bleMouse.click(MOUSE_MIDDLE);  // Middle Click
        Serial.println("Middle Click");
        delay(250);
    }

    if (digitalRead(L_BUT) == LOW) {
        bleMouse.click(MOUSE_LEFT);  // Left Click
        Serial.println("Left Click");
        delay(250);
    }

    if (digitalRead(R_BUT) == LOW) {
        bleMouse.click(MOUSE_RIGHT);  // Right Click
        Serial.println("Right Click");
        delay(250);
    }
}
