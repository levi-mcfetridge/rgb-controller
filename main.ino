#include <FastLED.h>

// ====== STRIP CONFIG ======
#define LED_PIN       5
#define NUM_LEDS      30 
#define LED_TYPE      WS2811
#define COLOR_ORDER   GRB
CRGB leds[NUM_LEDS];

// ====== FIXED BRIGHTNESS ======
const uint8_t BRIGHTNESS = 120; 

// ====== INPUT PINS ======
const uint8_t PIN_R    = A0;
const uint8_t PIN_G    = A1;
const uint8_t PIN_B    = A2;
const uint8_t PIN_SAVE = 2;       // momentary button: D2 -> 5V, with 10k pulldown to GND

// ====== SAVE / ANIMATION ======
const uint16_t SAVE_COOLDOWN_MS = 600;

uint8_t  colors[3][3];  // [slot][R/G/B]
uint8_t  colorSlot   = 0;

uint16_t pos         = 0;
uint32_t lastStep    = 0;
const uint16_t STEP_MS = 15;
uint32_t lastSaveMs  = 0;

// Helper to wrap LED index
inline uint16_t wrap(int32_t idx) {
  idx %= NUM_LEDS;
  if (idx < 0) idx += NUM_LEDS;
  return (uint16_t)idx;
}

void setup() {
  delay(3000); // power-up safety
  Serial.begin(115200);

  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS)
         .setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);

  // Button reads HIGH when pressed
  pinMode(PIN_SAVE, INPUT);

  FastLED.clear(true);
}

void loop() {
  // Read sliders 
  uint8_t r = map(analogRead(PIN_R), 0, 1023, 0, 255);
  uint8_t g = map(analogRead(PIN_G), 0, 1023, 0, 255);
  uint8_t b = map(analogRead(PIN_B), 0, 1023, 0, 255);

  // Non-blocking animation step
  uint32_t now = millis();
  if (now - lastStep >= STEP_MS) {
    lastStep = now;
    drawFrame(r, g, b);
    pos = wrap(pos + 1);
    FastLED.show();
  }

  // Save trigger on DIGITAL PIN 2 (pressed = HIGH)
  static bool prevState = LOW;
  bool curState = digitalRead(PIN_SAVE);

  if (prevState == LOW && curState == HIGH && (now - lastSaveMs) > SAVE_COOLDOWN_MS) {
    saveColor(r, g, b);
    lastSaveMs = now;
  }
  prevState = curState;
}

void drawFrame(uint8_t r, uint8_t g, uint8_t b) {
  // Live color at the moving pixel position
  leds[pos].setRGB(r, g, b);
  uint8_t numColors = colorSlot + 1;
  uint16_t step = NUM_LEDS / numColors;   // size of each segment
  for (uint8_t i = 0; i < colorSlot; i++) {
    uint16_t offset = step + i * step;
    leds[wrap(pos + offset)].setRGB(colors[i][0], colors[i][1], colors[i][2]);
  }
}

void saveColor(uint8_t r, uint8_t g, uint8_t b) {
  // Wipe to acknowledge the save
  for (uint16_t k = 0; k < NUM_LEDS; ++k) {
    leds[k].setRGB(r, g, b);
    if (k >= 5) leds[k - 5] = CRGB::Black;
    FastLED.show();
    delay(10);
  }
  FastLED.clear(true);

  colors[colorSlot][0] = r;
  colors[colorSlot][1] = g;
  colors[colorSlot][2] = b;

  colorSlot++;

  if(colorSlot == 3){
    colorSlot = 0;
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        colors[i][j] = 0;   // set every RGB value to 0
      }
    }
  }

  delay(120);
}
