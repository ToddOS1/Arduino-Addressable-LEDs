#include <FastLED.h>
#define NUM_LEDS_SET_1 (160 * 1) // Adjust the number of strips on pins for sets
#define NUM_LEDS_SET_2 (160 * 2)
#define DATA_PIN_1 11
#define DATA_PIN_2 9

// Only modify these:

int pulses = 2;
int delay_int = 100;

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
  for(int i = 0; i < pulses; i++){
    pulse_loc[i] = (total_LED / pulses) * i;
  }

  Serial.begin(9600);
}

void loop() {
  // Reset before next cycle
  fill_solid(leds1, NUM_LEDS_SET_1, CRGB::Black);
  fill_solid(leds2, NUM_LEDS_SET_2, CRGB::Black);

  // Increment pulse location and reset if needed
  for(int i = 0; i < pulses; i++){
    if(pulse_loc[i] >= total_LED){
      pulse_loc[i] = 0;
    } else {
      pulse_loc[i] += 1;
    }

    // Set LED colors
    if (pulse_loc[i] < NUM_LEDS_SET_1) {
      leds1[pulse_loc[i]] = CRGB(0, 0, 202); // Green
    } else {
      leds2[pulse_loc[i] - NUM_LEDS_SET_1] = CRGB(0, 0, 202); // Green
    }
  }

  // Display
  FastLED.show();
  FastLED.delay(delay_int);
}


/*
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
*/
