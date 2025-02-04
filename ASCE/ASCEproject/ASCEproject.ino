#include <FastLED.h>

#define NUM_LEDS 165  // Adjust the number of LEDs per strip
#define DATA_PIN_1 9
#define DATA_PIN_2 11
#define DATA_PIN_3 13

CRGB leds1[NUM_LEDS];
CRGB leds2[NUM_LEDS];
CRGB leds3[NUM_LEDS];

int currentLED = 0;
float lightPercent = 1;

void setup() {
    FastLED.addLeds<NEOPIXEL, DATA_PIN_1>(leds1, NUM_LEDS);
    FastLED.addLeds<NEOPIXEL, DATA_PIN_2>(leds2, NUM_LEDS);
    FastLED.addLeds<NEOPIXEL, DATA_PIN_3>(leds3, NUM_LEDS);
    FastLED.setBrightness((float)255 * lightPercent);
  for (int i = 0; i < NUM_LEDS / 2; i++) {
    leds1[i] = CRGB(255, 0, 0);  // Red color
  }
  for (int i = 0; i < NUM_LEDS; i++) {
    leds2[i] = CRGB(0, 0, 255);  // Green color
  }
  for (int i = NUM_LEDS / 2; i < NUM_LEDS; i++) {
    leds3[i] = CRGB(255, 0, 0);  // Red color
  }
  FastLED.show();
  delay(1000);
}

void loop() {
  leds2[currentLED] = CRGB::Black;

  // Move to the next LED
  currentLED++;

  // Reset to the beginning once all LEDs are turned off
  if (currentLED >= NUM_LEDS) {
    currentLED = 0;
    // Reinitialize all LEDs to green
    for (int i = 0; i < NUM_LEDS; i++) {
      leds2[i] = CRGB(0, 0, 255);  // Green color
    }
    delay(500);  // Optional delay before restarting the sequence
  }

  if(currentLED % 2 == 0){
    for (int i = 0; i < NUM_LEDS / 2; i++) {
      leds1[i] = CRGB(0, 0, 0);  // Red color
    }
  }else{
    for (int i = 0; i < NUM_LEDS / 2; i++) {
      leds1[i] = CRGB(255, 0, 0);  // Red color
    }
  }

  if(currentLED % 2 == 0){
    for (int i = NUM_LEDS / 2; i < NUM_LEDS; i++) {
      leds3[i] = CRGB(0, 0, 0);  // Red color
    }
  }else{
    for (int i = NUM_LEDS / 2; i < NUM_LEDS; i++) {
      leds3[i] = CRGB(255, 0, 0);  // Red color
    }
  }

  FastLED.show();
  delay(1000);  // Adjust delay for the speed at which LEDs turn off

}
