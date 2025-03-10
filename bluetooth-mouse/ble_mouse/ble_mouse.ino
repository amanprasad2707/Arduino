
#include <BleMouse.h>

BleMouse bleMouse;
int left_btn_pin = 23;
int right_btn_pin = 19;
int up_btn_pin = 4;
int down_btn_pin = 21;
int L_click_pin = 18;
int R_click_pin = 22;
int M_click_pin = 5;
int led_pin = 2;
bool L_flag;
bool R_flag;
bool M_flag;
void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE work!");
  bleMouse.begin();
  pinMode(left_btn_pin, INPUT_PULLUP);
  pinMode(right_btn_pin, INPUT_PULLUP);
  pinMode(up_btn_pin, INPUT_PULLUP);
  pinMode(down_btn_pin, INPUT_PULLUP);
  pinMode(L_click_pin, INPUT_PULLUP);
  pinMode(R_click_pin, INPUT_PULLUP);
  pinMode(M_click_pin, INPUT_PULLUP);
  pinMode(led_pin, OUTPUT);
}

void loop() {
  if (bleMouse.isConnected()) {
    bool move_left = digitalRead(left_btn_pin);
    bool move_right = digitalRead(right_btn_pin);
    bool move_up = digitalRead(up_btn_pin);
    bool move_down = digitalRead(down_btn_pin);
    bool L_click = digitalRead(L_click_pin);
    bool R_Click = digitalRead(R_click_pin);
    bool M_click = digitalRead(M_click_pin);

    if (L_click) {
      if (!move_left && move_right) {
        bleMouse.move(-5, 0);
        delay(5);
      }
      if (!move_right && move_left) {
        bleMouse.move(5, 0);
        delay(5);
      }
      if (!move_right && !move_left) {
        bleMouse.move(0, 0, -1);
        delay(20);
      }

      if (!move_up && move_down) {
        bleMouse.move(0, -5);
        delay(5);
      }
      if (!move_down && move_up) {
        bleMouse.move(0, 5);
        delay(5);
      }
      if (!move_down && !move_up) {
        bleMouse.move(0, 0, 1);
        delay(20);
      }
    } else {
      if (!move_left) {
        bleMouse.move(0, 0, 0, -1);
        delay(50);
      }
      if (!move_right) {
        bleMouse.move(0, 0, 0, 1);
        delay(50);
      }
      if (!move_up) {
        bleMouse.move(0, 0, 1);
        delay(50);
      }
      if (!move_down) {
        bleMouse.move(0, 0, -1);
        delay(50);
      }
    }

    //if (!L_click){if(!L_flag){bleMouse.click(MOUSE_FORWARD);delay(100);  L_flag=1;}} else{L_flag=0;}
    if (!R_Click) {
      if (!R_flag) {
        bleMouse.click(MOUSE_BACK);
        delay(100);
        R_flag = 1;
      }
    } else {
      R_flag = 0;
    }
    if (!M_click) {
      if (!M_flag) {
        bleMouse.press(MOUSE_LEFT);
        delay(100);
        M_flag = 1;
      }
    } else {
      M_flag = 0;
      if (bleMouse.isPressed(MOUSE_LEFT)) { bleMouse.release(MOUSE_LEFT); }
    }
    delay(15);

  } else {
    digitalWrite(led_pin, HIGH);
    delay(200);
    digitalWrite(led_pin, LOW);
    delay(200);
  }
}
