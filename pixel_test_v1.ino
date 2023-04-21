#include <Adafruit_NeoPixel.h>

#define PIN_NEOPIXEL_STRIP  4
#define NUM_PIXELS          10

Adafruit_NeoPixel NeoPixel(NUM_PIXELS, PIN_NEOPIXEL_STRIP, NEO_GRB + NEO_KHZ800);

void setup()
{
  pinMode(A0, INPUT);
  NeoPixel.begin();
  Serial.begin(9600);
}

void loop()
{
  NeoPixel.clear();
  NeoPixel.show();
  
  // Read the potentiometer value
  float value = analogRead(A0);
  Serial.println(value);
  int green = value / float(1023) * 255;
  
  // Set the strip light values
  for (int pixel=0; pixel < NUM_PIXELS; pixel++) {
    NeoPixel.setPixelColor(pixel, NeoPixel.Color(255 - green, green, 0));
    NeoPixel.show();  // show NeoPixel one by one
    delay(100);
  }
  
  delay(100);
}
