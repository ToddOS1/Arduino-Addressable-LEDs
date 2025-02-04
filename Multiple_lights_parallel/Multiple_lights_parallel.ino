#include <FastLED.h>

#define NUM_LEDS 160  // Adjust the number of LEDs to match your setup
#define DATA_PIN_1 8
#define DATA_PIN_2 9
#define PULSE_COUNT 1  // Number of simultaneous pulses
#define PULSE_INTERVAL 10  // Interval between pulses
#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))

CRGB leds1[NUM_LEDS];
CRGB leds2[NUM_LEDS];
int pulsePositions1[PULSE_COUNT];  // Array to track pulse positions for DATA_PIN_1
int pulsePositions2[PULSE_COUNT];  // Array to track pulse positions for DATA_PIN_2
bool firstPinActive = true;
bool secondPinActive = false;

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN_1>(leds1, NUM_LEDS);
  FastLED.addLeds<NEOPIXEL, DATA_PIN_2>(leds2, NUM_LEDS);
  FastLED.setBrightness(255);
  Serial.begin(9600);
  
  // Initialize pulse positions
  for (int i = 0; i < PULSE_COUNT; i++) {
    pulsePositions1[i] = NUM_LEDS - 1;  // Start at the end for reverse direction
    pulsePositions2[i] = -i * PULSE_INTERVAL;  // Start from the beginning for normal direction
  }
}

void loop() {
  int R = 0;
  int B = 0;
  int G = 202;
  
  // Clear the LED strips
  for (int i = 0; i < NUM_LEDS; i++) {
    leds1[i] = CRGB::Black;
    leds2[i] = CRGB::Black;
  }

  // Update pulse positions and set LED colors for DATA_PIN_1
  if (firstPinActive) {
    for (int p = 0; p < PULSE_COUNT; p++) {
      int pos = pulsePositions1[p];
      if (pos >= 0 && pos < NUM_LEDS) {
        leds1[pos] = CRGB(R, B, G);
        if (pos - 2 >= 0) {
          leds1[pos - 2] = CRGB(R / 100, B / 100, G / 100);
        }
        if (pos - 1 >= 0) {
          leds1[pos - 1] = CRGB(R / 100, B / 100, G / 100);
        }
        if (pos + 1 < NUM_LEDS) {
          leds1[pos + 1] = CRGB(R / 100, B / 100, G / 100);
        }
        if (pos + 2 < NUM_LEDS) {
          leds1[pos + 2] = CRGB::Black;
        }
      }
      pulsePositions1[p]--;
      
      // Check if the pulse has moved past the start position
      if (pulsePositions1[p] < 0) {
        pulsePositions1[p] = NUM_LEDS - 1;  // Reset to end position
        firstPinActive = false;
        secondPinActive = true;  // Switch to the second pin
      }
    }
  }

  // Update pulse positions and set LED colors for DATA_PIN_2
  if (secondPinActive) {
    for (int p = 0; p < PULSE_COUNT; p++) {
      int pos = pulsePositions2[p];
      if (pos >= 0 && pos < NUM_LEDS) {
        leds2[pos] = CRGB(R, B, G);
        if (pos + 2 < NUM_LEDS) {
          leds2[pos + 2] = CRGB(R / 100, B / 100, G / 100);
        }
        if (pos + 1 < NUM_LEDS) {
          leds2[pos + 1] = CRGB(R / 100, B / 100, G / 100);
        }
        if (pos > 0) {
          leds2[pos - 1] = CRGB(R / 100, B / 100, G / 100);
        }
        if (pos > 1) {
          leds2[pos - 2] = CRGB::Black;
        }
      }
      pulsePositions2[p]++;
      
      // Check if the pulse has reached or exceeded the maximum position
      if (pulsePositions2[p] >= NUM_LEDS) {
        pulsePositions2[p] = -PULSE_INTERVAL * PULSE_COUNT + p * PULSE_INTERVAL;
        secondPinActive = false;
        firstPinActive = true;  // Switch back to the first pin
      }
    }
  }

  FastLED.show();
  delay(50);  // Adjust delay for speed of pulses
}
