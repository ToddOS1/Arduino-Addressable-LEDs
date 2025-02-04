#include <FastLED.h>

#define NUM_LEDS 165  // Adjust the number of LEDs per strip
#define DATA_PIN_1 11
#define DATA_PIN_2 9


CRGB leds1[NUM_LEDS];
CRGB leds2[NUM_LEDS];
int currentLED = 0;  // Track the current LED to turn off

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN_1>(leds1, NUM_LEDS);
  FastLED.addLeds<NEOPIXEL, DATA_PIN_2>(leds2, NUM_LEDS);
  FastLED.setBrightness(255);

  // Initialize all LEDs to green
  for (int i = 0; i < NUM_LEDS; i++) {
    leds1[i] = CRGB(0, 0, 255);  // Green color
    leds2[i] = CRGB(0, 0, 255);  // Green color
  }

  FastLED.show();
  delay(1000);  // Give some time to see all LEDs green before starting to turn them off
}

void loop() {
  // Turn off the current LED
  leds1[currentLED] = CRGB::Black;
  leds2[currentLED] = CRGB::Black;

  // Move to the next LED
  currentLED++;

  // Reset to the beginning once all LEDs are turned off
  if (currentLED >= NUM_LEDS) {
    currentLED = 0;
    // Reinitialize all LEDs to green
    for (int i = 0; i < NUM_LEDS; i++) {
      leds1[i] = CRGB(0, 0, 255);  // Green color
      leds2[i] = CRGB(0, 0, 255);  // Green color
    }
    delay(500);  // Optional delay before restarting the sequence
  }

  FastLED.show();
  delay(1000);  // Adjust delay for the speed at which LEDs turn off
}
