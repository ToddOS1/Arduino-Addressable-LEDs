#include <FastLED.h>

// Define the number of LEDs in the strip
#define NUM_LEDS 320

// Define the pin for the data input
#define LED_PIN 11

// Create an array of LED objects
CRGB leds[NUM_LEDS];

void setup() {
  // Initialize the LED strip
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  // Set initial brightness
  FastLED.setBrightness(255);
}

void loop() {
  // Loop through each LED and set it to a random color
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(random(0, 256), 255, 255); // Hue, Saturation, Value
  }
  
  // Show the colors
  FastLED.show();
  
  // Wait for a while before changing colors again
  delay(1);
}
