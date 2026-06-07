// ============================================================
//  Birthday Surprise — ESP32 FreeRTOS Dual-Core Edition
//  Core 0 → Audio (Happy Birthday melody, blocking tone loop)
//  Core 1 → UI   (OLED animations, scene state machine)
//
//  WIRING:
//    OLED SDA → GPIO 21 | SCL → GPIO 22
//    Buzzer (+) → GPIO 19 | Buzzer (−) → GPIO 23  ← NOT GND
// ============================================================
//  Libraries: Adafruit SSD1306 + Adafruit GFX
// ============================================================

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ─── Pins ────────────────────────────────────────────────────
#define BUZ1          19
#define BUZ2          23
#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define OLED_ADDR     0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// ─── Melody (exact from your reference) ─────────────────────
// Each row: { frequency_hz, note_ms, pause_ms }
const int melody[][3] = {
  {264, 250, 50}, {264, 250, 50}, {297, 500, 50},
  {264, 500, 50}, {352, 500, 50}, {330,1000,200},
  {264, 250, 50}, {264, 250, 50}, {297, 500, 50},
  {264, 500, 50}, {396, 500, 50}, {352,1000,200},
  {264, 250, 50}, {264, 250, 50}, {528, 500, 50},
  {440, 500, 50}, {352, 500, 50}, {330, 500, 50},
  {297,1000,200}, {466, 250, 50}, {466, 250, 50},
  {440, 500, 50}, {352, 500, 50}, {396, 500, 50},
  {352,1200,  0}
};
const int melodyLen = sizeof(melody) / sizeof(melody[0]);

// ─── Shared state (audio ↔ UI sync) ─────────────────────────
volatile bool     audioStarted  = false;   // UI sets true → audio task begins
volatile bool     audioDone     = false;   // audio task sets true when finished
volatile int      currentNote   = 0;       // which note is playing right now
SemaphoreHandle_t displayMutex;            // guards I2C / display calls

// ─── Scene enum ──────────────────────────────────────────────
enum Scene {
  SCENE_INTRO,
  SCENE_SPARKLE,
  SCENE_CAKE,
  SCENE_CUTTING,
  SCENE_HEARTS,
  SCENE_MESSAGE,
  SCENE_FIREWORKS,
  SCENE_DONE
};

// ─── UI state (only touched by Core 1) ───────────────────────
Scene         currentScene = SCENE_INTRO;
unsigned long sceneStart   = 0;
bool          candleLit    = true;
int           cakeSlice    = 0;
int           candleFrame  = 0;

// ════════════════════════════════════════════════════════════
//  CORE 0 — AUDIO TASK
// ════════════════════════════════════════════════════════════
void audioTask(void* param) {
  // Wait until UI signals go
  while (!audioStarted) vTaskDelay(1);

  while(1){
    for (int n = 0; n < melodyLen; n++) {
      currentNote = n;
      int freq = melody[n][0];
      int dur  = melody[n][1];
      int pau  = melody[n][2];

      // Blocking tone — pure CPU loop, no delay(), no RTOS overhead
      long cycles   = (long)freq * dur / 1000;
      long halfUs   = 1000000L / (freq * 2);
      for (long i = 0; i < cycles; i++) {
        digitalWrite(BUZ1, HIGH); digitalWrite(BUZ2, LOW);
        delayMicroseconds(halfUs);
        digitalWrite(BUZ1, LOW);  digitalWrite(BUZ2, HIGH);
        delayMicroseconds(halfUs);
      }
    digitalWrite(BUZ1, LOW); digitalWrite(BUZ2, LOW);

    if (pau > 0) vTaskDelay(pdMS_TO_TICKS(pau));
    }
  }

  audioDone = true;
  vTaskDelete(NULL);  // self-delete when melody finishes
}

// ════════════════════════════════════════════════════════════
//  DRAWING HELPERS  (all called from Core 1 only)
// ════════════════════════════════════════════════════════════
void drawStar(int x, int y) {
  display.drawPixel(x,     y,     WHITE);
  display.drawPixel(x - 1, y - 1, WHITE);
  display.drawPixel(x + 1, y - 1, WHITE);
  display.drawPixel(x - 1, y + 1, WHITE);
  display.drawPixel(x + 1, y + 1, WHITE);
  display.drawPixel(x,     y - 2, WHITE);
  display.drawPixel(x,     y + 2, WHITE);
  display.drawPixel(x - 2, y,     WHITE);
  display.drawPixel(x + 2, y,     WHITE);
}

void drawHeart(int x, int y, int size) {
  int r = size / 2;
  display.fillCircle(x - r, y, r, WHITE);
  display.fillCircle(x + r, y, r, WHITE);
  display.fillTriangle(x - size, y, x + size, y, x, y + size + 2, WHITE);
}

void drawCandle(int x, int y, bool lit, int frame) {
  display.fillRect(x - 2, y, 4, 12, WHITE);
  if (lit) {
    int fx = x + (frame % 3) - 1;
    display.fillCircle(fx, y - 3, 3, WHITE);
    display.fillCircle(x,  y - 5, 2, WHITE);
  }
}

void drawCake(bool showKnife, int sliceAnim) {
  int cx = 64;
  display.fillRoundRect(cx - 28, 36, 56, 14, 3, WHITE);  // was 44
  display.fillRoundRect(cx - 20, 22, 40, 16, 3, WHITE);  // was 30
  for (int i = 0; i < 5; i++)
    display.fillCircle(cx - 16 + i * 8, 32, 2, BLACK);
  display.fillRoundRect(cx - 32, 48, 64, 5,  2, WHITE);  // was 56
  for (int i = 0; i < 5; i++)
    display.fillCircle(cx - 20 + i * 10, 50, 2, BLACK);
  drawCandle(cx - 12, 14, candleLit, candleFrame);
  drawCandle(cx,      14, candleLit, candleFrame + 1);
  drawCandle(cx + 12, 14, candleLit, candleFrame + 2);
  if (showKnife && sliceAnim > 0) {
    int ky = max(10, 35 - sliceAnim * 5);
    display.drawLine(cx + 24, ky, cx + 24, ky + 18, WHITE);
    display.fillTriangle(cx + 21, ky + 18, cx + 27, ky + 18, cx + 24, ky + 24, WHITE);
    if (sliceAnim > 4) {
      display.drawLine(cx + 8, 30, cx + 8, 58, BLACK);
      display.drawLine(cx + 9, 30, cx + 9, 58, BLACK);
    }
  }
}

void drawFirework(int cx, int cy, int r) {
  for (int a = 0; a < 360; a += 30) {
    float rad = a * PI / 180.0f;
    int x1 = cx + (int)(r * 0.3f * cosf(rad));
    int y1 = cy + (int)(r * 0.3f * sinf(rad));
    int x2 = cx + (int)(r * cosf(rad));
    int y2 = cy + (int)(r * sinf(rad));
    display.drawLine(x1, y1, x2, y2, WHITE);
  }
}

void scrollText(const char* txt, int y, unsigned long t) {
  int tw = strlen(txt) * 6;
  int x  = SCREEN_WIDTH - (int)(t / 8) % (tw + SCREEN_WIDTH);
  display.setCursor(x, y);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.print(txt);
  if (x < 0) {
    display.setCursor(x + tw + SCREEN_WIDTH, y);
    display.print(txt);
  }
}

// ════════════════════════════════════════════════════════════
//  SCENE RENDERERS
// ════════════════════════════════════════════════════════════
void renderIntro(unsigned long e) {
  display.clearDisplay();

  // Expanding ring pulse
  int ring = (e / 6) % 34;
  display.drawCircle(64, 32, ring,       WHITE);
  display.drawCircle(64, 32, max(0, ring - 10), WHITE);

  // Rotating stars around center
  for (int i = 0; i < 6; i++) {
    float angle = (e / 600.0f) + i * (PI / 3.0f);
    int sx = 64 + (int)(22 * cosf(angle));
    int sy = 32 + (int)(22 * sinf(angle));
    drawStar(sx, sy);
  }

  // "Happy" slides in from left, "Birthday" from right
  int offset = min(0, (int)(e / 10) - 80);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(offset + 22, 24);
  display.print("Happy");
  display.setCursor(-offset + 22, 34);
  display.print("Birthday!");

  display.display();
}

void renderSparkle(unsigned long e) {
  display.clearDisplay();
  int phase = (e / 70) % 18;
  for (int i = 0; i < 20; i++) {
    float angle = i * 18.0f * PI / 180.0f;
    int r  = 4 + phase * 2;
    int sx = 64 + (int)(r * cosf(angle));
    int sy = 32 + (int)(r * sinf(angle));
    if (sx >= 0 && sx < 128 && sy >= 0 && sy < 64)
      drawStar(sx, sy);
  }
  drawStar(64, 32);
  display.display();
}

void renderCake(unsigned long e) {
  candleFrame = (e / 180) % 3;
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(14, 0);
  display.print("Your Special Cake!");
  drawCake(false, 0);
  scrollText("  Happy Birthday!  ", 56, e);
  display.display();
}

void renderCutting(unsigned long e) {
  cakeSlice   = min(8, (int)(e / 180));
  candleFrame = (e / 180) % 3;
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(22, 0);
  display.print("Make a wish...");
  drawCake(true, cakeSlice);
  if (cakeSlice >= 8) {
    if (e > 1800) candleLit = false;
    display.setCursor(50, 56);
    display.print("SLICE!");
  }
  display.display();
}

void renderHearts(unsigned long e) {
  display.clearDisplay();
  const int px[] = {18, 48, 78, 106, 33, 90};
  const int py[] = {28, 14, 33,  18, 46, 48};
  const int sz[] = { 6,  4,  8,   5,  6,  4};
  for (int i = 0; i < 6; i++) {
    int yo = (int)(3.0f * sinf(e / 380.0f + i));
    drawHeart(px[i], py[i] + yo, sz[i]);
  }
  display.setTextSize(1);
  display.setCursor(22, 56);
  display.print("With love  <3");
  display.display();
}

void renderMessage(unsigned long e) {
  display.clearDisplay();
  const char* lines[] = {
    "You make every",
    "day brighter.",
    "Stay awesome!",
    ":)"
  };
  int total = min(60, (int)(e / 75));
  for (int l = 0; l < 4; l++) {
    int start = l * 15;
    if (total > start) {
      int chars = min((int)strlen(lines[l]), total - start);
      char buf[16] = {0};
      strncpy(buf, lines[l], chars);
      display.setTextSize(1);
      display.setCursor(5, 4 + l * 15);
      display.print(buf);
    }
  }
  // Blinking cursor
  if ((e / 480) % 2 == 0) {
    int line = min(3, total / 15);
    int col  = total % 15;
    display.fillRect(5 + col * 6, 4 + line * 15, 5, 8, WHITE);
  }
  display.display();
}

void renderFireworks(unsigned long e) {
  display.clearDisplay();
  const int fwx[] = {20, 100, 55,  80, 30};
  const int fwy[] = {15,  20, 10,  40, 45};
  const int fwd[] = { 0, 400, 200, 600, 800};
  for (int i = 0; i < 5; i++) {
    long lt = (long)e - fwd[i];
    if (lt < 0) continue;
    int phase = (lt / 70) % 20;
    int r = (phase < 10) ? phase * 3 : (20 - phase) * 3;
    if (r > 0) drawFirework(fwx[i], fwy[i], r);
  }
  display.setTextSize(1);
  display.setCursor(16, 56);
  display.print("Celebrate!!!  :D");
  display.display();
}

void renderDone(unsigned long e) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(12, 4);
  display.print("May all your");
  display.setCursor(8, 18);
  display.print("dreams come true");
  drawHeart(64, 42, 10);
  if ((e / 550) % 2 == 0) {
    drawStar(18, 38); drawStar(110, 38);
  }
  display.display();
}

// ─── Scene transition ─────────────────────────────────────────
void nextScene() {
  currentScene = (Scene)((int)currentScene + 1);
  sceneStart   = millis();
  candleLit    = true;
}

// ════════════════════════════════════════════════════════════
//  CORE 1 — UI TASK  (runs as normal Arduino loop())
// ════════════════════════════════════════════════════════════
void setup() {
  Serial.begin(115200);

  pinMode(BUZ1, OUTPUT); pinMode(BUZ2, OUTPUT);
  digitalWrite(BUZ1, LOW); digitalWrite(BUZ2, LOW);

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println("OLED init failed");
    while (true);
  }
  display.clearDisplay();
  display.display();

  // Launch audio task on Core 0, high priority, 2KB stack
  xTaskCreatePinnedToCore(audioTask, "Audio", 2048, NULL, configMAX_PRIORITIES - 1, NULL, 0);
  audioStarted = true;
  sceneStart = millis();
}

void loop() {
  unsigned long now     = millis();
  unsigned long elapsed = now - sceneStart;

  switch (currentScene) {

    case SCENE_INTRO:
      renderIntro(elapsed);
      if (elapsed > 5000) {
        nextScene();          // → SPARKLE
        // audioStarted = true;  // kick off music on Core 0
      }
      break;

    case SCENE_SPARKLE:
      renderSparkle(elapsed);
      if (elapsed > 2000) nextScene();
      break;

    case SCENE_CAKE:
      renderCake(elapsed);
      if (elapsed > 5000) nextScene();
      break;

    case SCENE_CUTTING:
      renderCutting(elapsed);
      if (elapsed > 3800) nextScene();
      break;

    case SCENE_HEARTS:
      renderHearts(elapsed);
      if (elapsed > 4000) nextScene();
      break;

    case SCENE_MESSAGE:
      renderMessage(elapsed);
      if (elapsed > 6500) nextScene();
      break;

    case SCENE_FIREWORKS:
      renderFireworks(elapsed);
      if (elapsed > 5000) nextScene();
      break;

    case SCENE_DONE:
      renderDone(elapsed);
      // Auto-replay once audio finishes: loop back to intro
      if (audioDone && elapsed > 3000) {
        currentScene = SCENE_INTRO;
        sceneStart   = millis();
        candleLit    = true;
      }
      break;
  }

  // ~30 fps — keeps I2C bus happy without overloading
  vTaskDelay(pdMS_TO_TICKS(33));
}
