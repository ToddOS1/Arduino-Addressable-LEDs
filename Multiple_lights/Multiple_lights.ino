#include <FastLED.h>

#define NUM_LEDS 160  // Adjust the number of LEDs per strip
#define DATA_PIN_1 11
#define DATA_PIN_2 8
#define PULSE_COUNT 1  // Number of simultaneous pulses
#define PULSE_INTERVAL 10  // Interval between pulses

CRGB leds1[NUM_LEDS];
CRGB leds2[NUM_LEDS];
int pulsePositions[PULSE_COUNT];  // Array to track pulse positions

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN_1>(leds1, NUM_LEDS);
  FastLED.addLeds<NEOPIXEL, DATA_PIN_2>(leds2, NUM_LEDS);
  FastLED.setBrightness(255);
  Serial.begin(9600);
  // Initialize pulse positions at intervals
  for (int i = 0; i < PULSE_COUNT; i++) {
    pulsePositions[i] = -i * PULSE_INTERVAL;
  }
}

void loop() {
  int R = 0;
  int B = 0;
  int G = 202;
  // Clear both LED strips
  for (int i = 0; i < NUM_LEDS; i++) {
    leds1[i] = CRGB::Black;
    leds2[i] = CRGB::Black;
  }

  // Update pulse positions and set LED colors
  for (int p = 0; p < PULSE_COUNT; p++) {
    int pos = pulsePositions[p];
    if (pos >= 0 && pos < NUM_LEDS) {
      leds1[pos] = CRGB(R, B, G);
      leds2[pos] = CRGB(R, B, G);
      if (pos + 2 < NUM_LEDS) {
        leds1[pos + 2] = CRGB(R / 100, B / 100, G / 100);
        leds2[pos + 2] = CRGB(R / 100, B / 100, G / 100);
      }
      if (pos + 1 < NUM_LEDS) {
        leds1[pos + 1] = CRGB(R / 100, B / 100, G / 100);
        leds2[pos + 1] = CRGB(R / 100, B / 100, G / 100);
      }
      if (pos > 0) {
        leds1[pos - 1] = CRGB(R / 100, B / 100, G / 100);
        leds2[pos - 1] = CRGB(R / 100, B / 100, G / 100);
      }
      if (pos > 1) {
        leds1[pos - 2] = CRGB::Black;
        leds2[pos - 2] = CRGB::Black;
      }
    }
    pulsePositions[p]++;
  }

  // Reset pulses that have moved past the end
  for (int p = 0; p < PULSE_COUNT; p++) {
    if (pulsePositions[p] >= NUM_LEDS) {
      pulsePositions[p] = -PULSE_INTERVAL * PULSE_COUNT + p * PULSE_INTERVAL;
    }
  }

  FastLED.show();
  delay(500);  // Adjust delay for speed of pulses
}
