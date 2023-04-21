#include <Adafruit_NeoPixel.h>

#define LED_PIN 7
#define LED_COUNT 24
#define SWITCH_PIN 3

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
int offset = 0;

void setup() {
  strip.begin();
  strip.setBrightness(100);
  pinMode(SWITCH_PIN, INPUT_PULLUP); // Enable internal pull-up resistor for the switch pin
}

void loop() {
  if (digitalRead(SWITCH_PIN) == HIGH)
    rainbowCycle(); // Activate rainbow color effect
  else
    strip.clear();
  strip.show();
  delay(20);
}

void rainbowCycle() {
  strip.clear();
  for (int i=0; i < LED_COUNT; i++) {
    int pos = 255 - ((i * 256 / LED_COUNT) + offset) & 255;
    if (pos < 85)
      strip.setPixelColor(i, strip.Color(255 - pos * 3, 0, pos * 3));
    else if (pos < 170) {
      pos -= 85;
      strip.setPixelColor(i, strip.Color(0, pos * 3, 255 - pos * 3));
    }
    else {
      pos -= 170;
      strip.setPixelColor(i, strip.Color(pos * 3, 255 - pos * 3, 0));
    }
  }
  offset = (offset + 1) % 256;
}
