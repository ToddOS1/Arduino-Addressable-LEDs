#include <FastLED.h>

#define NUM_LEDS_SET_1 (160 * 1) // Adjust the number of strips on pins for sets
#define NUM_LEDS_SET_2 (160 * 1)
#define DATA_PIN_1 11 // Pin 11: max index to min index
#define DATA_PIN_2 9  // Pin 9: min index to max index

// Only modify these:
int pulses = 4;      // Equal divisions along the lights
int pulse_length = 10; // Length of each pulse in LEDs
int delay_int = 40;  // Speed of traveling light

// Don't modify below this for standard parameters
int total_LED = NUM_LEDS_SET_1 + NUM_LEDS_SET_2;
int* pulse_loc;

CRGB leds1[NUM_LEDS_SET_1];
CRGB leds2[NUM_LEDS_SET_2];

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN_1>(leds1, NUM_LEDS_SET_1);
  FastLED.addLeds<NEOPIXEL, DATA_PIN_2>(leds2, NUM_LEDS_SET_2);
  FastLED.setBrightness(255);
  pulse_loc = new int[pulses];
  for (int i = 0; i < pulses; i++) {
    pulse_loc[i] = (total_LED / pulses) * i;
  }

  Serial.begin(9600);
}

void loop() {
  // Reset before next cycle
  fill_solid(leds1, NUM_LEDS_SET_1, CRGB::Black);
  fill_solid(leds2, NUM_LEDS_SET_2, CRGB::Black);

  // Increment pulse location and reset if needed
  for (int i = 0; i < pulses; i++) {
    if (pulse_loc[i] >= total_LED) {
      pulse_loc[i] = 0;
    } else {
      pulse_loc[i] += 1;
    }

    // Draw pulse with specified length
    for (int j = 0; j < pulse_length; j++) {
      int pos = pulse_loc[i] - j;
      if (pos < 0) pos += total_LED; // Wrap around if needed

      // Set LED colors
      if (pos < NUM_LEDS_SET_1) {
        leds1[NUM_LEDS_SET_1 - pos] = CRGB(0, 0, 202); // Green
      } else {
        leds2[pos - NUM_LEDS_SET_1] = CRGB(0, 0, 202); // Green
      }
    }
  }

  // Display
  FastLED.show();
  FastLED.delay(delay_int);
}
