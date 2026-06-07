#define BUZ1 19
#define BUZ2 23

// Function to generate loud tone using push-pull drive
void playTone(int freq, int duration) {

  long cycles = (long)freq * duration / 1000;

  long delayTime = 1000000L / (freq * 2);

  for (long i = 0; i < cycles; i++) {

    digitalWrite(BUZ1, HIGH);
    digitalWrite(BUZ2, LOW);
    delayMicroseconds(delayTime);

    digitalWrite(BUZ1, LOW);
    digitalWrite(BUZ2, HIGH);
    delayMicroseconds(delayTime);
  }
}

void pauseTone(int duration) {
  digitalWrite(BUZ1, LOW);
  digitalWrite(BUZ2, LOW);
  delay(duration);
}

void setup() {
  pinMode(BUZ1, OUTPUT);
  pinMode(BUZ2, OUTPUT);
}

void loop() {

  // Happy Birthday Melody

  playTone(264, 250);
  pauseTone(50);

  playTone(264, 250);
  pauseTone(50);

  playTone(297, 500);
  pauseTone(50);

  playTone(264, 500);
  pauseTone(50);

  playTone(352, 500);
  pauseTone(50);

  playTone(330, 1000);
  pauseTone(200);

  playTone(264, 250);
  pauseTone(50);

  playTone(264, 250);
  pauseTone(50);

  playTone(297, 500);
  pauseTone(50);

  playTone(264, 500);
  pauseTone(50);

  playTone(396, 500);
  pauseTone(50);

  playTone(352, 1000);
  pauseTone(200);

  playTone(264, 250);
  pauseTone(50);

  playTone(264, 250);
  pauseTone(50);

  playTone(528, 500);
  pauseTone(50);

  playTone(440, 500);
  pauseTone(50);

  playTone(352, 500);
  pauseTone(50);

  playTone(330, 500);
  pauseTone(50);

  playTone(297, 1000);
  pauseTone(200);

  playTone(466, 250);
  pauseTone(50);

  playTone(466, 250);
  pauseTone(50);

  playTone(440, 500);
  pauseTone(50);

  playTone(352, 500);
  pauseTone(50);

  playTone(396, 500);
  pauseTone(50);

  playTone(352, 1200);

  delay(3000);
}