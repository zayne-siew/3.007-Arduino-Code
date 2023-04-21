#include <Adafruit_NeoPixel.h>

#define PIN_NEOPIXEL 2
#define PIN_BUTTON 3

#define NUM_PIXELS 22

Adafruit_NeoPixel NP(NUM_PIXELS, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  pinMode(PIN_BUTTON, INPUT_PULLUP);
  NP.begin();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int state = digitalRead(PIN_BUTTON);
  //Serial.println(state);
  if (state == LOW) {
    for (int pixel = 0; pixel < NUM_PIXELS; pixel++)
      NP.setPixelColor(pixel, NP.Color(255, 105, 180));
    NP.show();
    delay(300);
    NP.clear();
    NP.show();
    while (digitalRead(PIN_BUTTON) == LOW)
      delay(10);
  }
  delay(10);
}
