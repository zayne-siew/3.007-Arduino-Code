#include <Adafruit_NeoPixel.h>

#define PIN_POTENTIOMETER A0
#define PIN_NEOPIXEL_1 2
#define PIN_NEOPIXEL_2 3
#define PIN_NEOPIXEL_3 4
#define PIN_NEOPIXEL_4 5
#define PIN_NEOPIXEL_5 6

#define NUM_PIXELS 4
#define DEFAULT_GLOW 5
#define DEFAULT_FILL 0
#define DEFAULT_DRAIN 0

Adafruit_NeoPixel NP1(NUM_PIXELS, PIN_NEOPIXEL_1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel NP2(NUM_PIXELS, PIN_NEOPIXEL_2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel NP3(NUM_PIXELS, PIN_NEOPIXEL_3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel NP4(NUM_PIXELS, PIN_NEOPIXEL_4, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel NP5(NUM_PIXELS, PIN_NEOPIXEL_5, NEO_GRB + NEO_KHZ800);

// To determine if animation is played
float prev_potentiometer_value = 0;
float threshold = 25;

// For glow animation
int curr_glow = DEFAULT_GLOW;
int glow_increment = 25;
int increase_glow = 0;

// For fill animation
int curr_fill = DEFAULT_FILL;
int fill_increment = 1;

// For drain animation
int curr_drain = DEFAULT_DRAIN;
int drain_increment = 1;

void setup() {
  pinMode(PIN_POTENTIOMETER, INPUT);
  NP1.begin();
  NP2.begin();
  NP3.begin();
  NP4.begin();
  NP5.begin();
  Serial.begin(9600);
}

void loop() {
  // Clear any lights from the previous iteration
  NP1.clear();
  NP1.show();
  NP2.clear();
  NP2.show();
  NP3.clear();
  NP3.show();
  NP4.clear();
  NP4.show();
  NP5.clear();
  NP5.show();
  // Read the potentiometer value
  float curr_potentiometer_value = analogRead(PIN_POTENTIOMETER);
  // Check if the potentiometer value has decreased
  if (prev_potentiometer_value - curr_potentiometer_value >= threshold) {
    curr_glow = DEFAULT_GLOW;
    curr_fill = DEFAULT_FILL;
    drain(0, 255, 0);
  }
  // Check if the potentiometer value has increased
  else if (curr_potentiometer_value - prev_potentiometer_value >= threshold) {
    glow(0, 0, 255);
    //fill(255, 0, 0);
  }
  // Check if the drain animation is still supposed to be playing
  else if (curr_drain > DEFAULT_DRAIN)
    drain(0, 255, 0);
  // Check if the glow animation is still supposed to be playing
  else if (curr_glow > DEFAULT_GLOW) {
    glow(0, 0, 255);
    //fill(255, 0, 0);
  }
  prev_potentiometer_value = curr_potentiometer_value;
  // Delay till the next iteration
  delay(100);
}

void glow(int r, int g, int b) {
  curr_glow += pow(-1, increase_glow) * glow_increment;
  for (int pixel = 0; pixel < NUM_PIXELS; pixel++)
    NP1.setPixelColor(pixel, NP1.Color(r * curr_glow / 255, g * curr_glow / 255, b * curr_glow / 255));
  NP1.show();
  for (int pixel = 0; pixel < NUM_PIXELS; pixel++)
    NP2.setPixelColor(pixel, NP2.Color(r * curr_glow / 255, g * curr_glow / 255, b * curr_glow / 255));
  NP2.show();
  for (int pixel = 0; pixel < NUM_PIXELS; pixel++)
    NP3.setPixelColor(pixel, NP3.Color(r * curr_glow / 255, g * curr_glow / 255, b * curr_glow / 255));
  NP3.show();
  for (int pixel = 0; pixel < NUM_PIXELS; pixel++)
    NP4.setPixelColor(pixel, NP4.Color(r * curr_glow / 255, g * curr_glow / 255, b * curr_glow / 255));
  NP4.show();
  for (int pixel = 0; pixel < NUM_PIXELS; pixel++)
    NP5.setPixelColor(pixel, NP5.Color(r * curr_glow / 255, g * curr_glow / 255, b * curr_glow / 255));
  NP5.show();
  if (curr_glow == DEFAULT_GLOW || curr_glow == 255)
    increase_glow = 1 - increase_glow;
}

void fill(int r, int g, int b) {
  curr_fill += fill_increment;
  for (int pixel = 0; pixel < NUM_PIXELS; pixel++) {
    int rank = pixel;
    if (rank <= curr_fill && (rank + curr_fill) % 2 == 1)
      NP1.setPixelColor(pixel, NP1.Color(r, g, b));
  }
  NP1.show();
  for (int pixel = 0; pixel < NUM_PIXELS; pixel++) {
    int rank = pixel + 1;
    if (rank <= curr_fill && (rank + curr_fill) % 2 == 1)
      NP2.setPixelColor(pixel, NP2.Color(r, g, b));
  }
  NP2.show();
  for (int pixel = 0; pixel < NUM_PIXELS; pixel++) {
    int rank = pixel + 2;
    if (rank <= curr_fill && (rank + curr_fill) % 2 == 1)
      NP3.setPixelColor(pixel, NP3.Color(r, g, b));
  }
  NP3.show();
  for (int pixel = 0; pixel < NUM_PIXELS; pixel++) {
    int rank = pixel + 3;
    if (rank <= curr_fill && (rank + curr_fill) % 2 == 1)
      NP4.setPixelColor(pixel, NP4.Color(r, g, b));
  }
  NP4.show();
  for (int pixel = 0; pixel < NUM_PIXELS; pixel++) {
    int rank = pixel + 4;
    if (rank <= curr_fill && (rank + curr_fill) % 2 == 1)
      NP5.setPixelColor(pixel, NP5.Color(r, g, b));
  }
  NP5.show();
}

void drain(int r, int g, int b) {
  curr_drain += drain_increment;
  if (curr_drain == 13) {
    curr_drain = 0;
    return;
  }
  else if (curr_drain == 1) {
    NP1.setPixelColor(3, NP1.Color(r, g, b));
    NP1.show();
  }
  else if (curr_drain == 2) {
    NP1.setPixelColor(2, NP1.Color(r, g, b));
    NP2.setPixelColor(3, NP2.Color(r, g, b));
    NP1.show();
    NP2.show();
  }
  else if (curr_drain == 3) {
    NP1.setPixelColor(1, NP1.Color(r, g, b));
    NP2.setPixelColor(2, NP2.Color(r, g, b));
    NP3.setPixelColor(3, NP3.Color(r, g, b));
    NP1.show();
    NP2.show();
    NP3.show();
  }
  else if (curr_drain == 4) {
    NP1.setPixelColor(0, NP1.Color(r, g, b));
    NP2.setPixelColor(1, NP2.Color(r, g, b));
    NP3.setPixelColor(2, NP3.Color(r, g, b));
    NP4.setPixelColor(3, NP4.Color(r, g, b));
    NP1.show();
    NP2.show();
    NP3.show();
    NP4.show();
  }
  else if (curr_drain == 5) {
    NP2.setPixelColor(0, NP2.Color(r, g, b));
    NP3.setPixelColor(1, NP3.Color(r, g, b));
    NP4.setPixelColor(2, NP4.Color(r, g, b));
    NP5.setPixelColor(3, NP5.Color(r, g, b));
    NP2.show();
    NP3.show();
    NP4.show();
    NP5.show();
  }
  else if (curr_drain == 6) {
    NP1.setPixelColor(0, NP2.Color(r, g, b));
    NP3.setPixelColor(0, NP3.Color(r, g, b));
    NP4.setPixelColor(1, NP4.Color(r, g, b));
    NP5.setPixelColor(2, NP5.Color(r, g, b));
    NP1.show();
    NP3.show();
    NP4.show();
    NP5.show();
  }
  else if (curr_drain == 7) {
    NP2.setPixelColor(0, NP1.Color(r, g, b));
    NP4.setPixelColor(0, NP4.Color(r, g, b));
    NP5.setPixelColor(1, NP5.Color(r, g, b));
    NP2.show();
    NP4.show();
    NP5.show();
  }
  else if (curr_drain == 8) {
    NP1.setPixelColor(0, NP2.Color(r, g, b));
    NP3.setPixelColor(0, NP4.Color(r, g, b));
    NP5.setPixelColor(0, NP5.Color(r, g, b));
    NP1.show();
    NP3.show();
    NP5.show();
  }
  else if (curr_drain == 9) {
    NP2.setPixelColor(0, NP2.Color(r, g, b));
    NP4.setPixelColor(0, NP4.Color(r, g, b));
    NP2.show();
    NP4.show();
  }
  else if (curr_drain == 10) {
    NP1.setPixelColor(0, NP1.Color(r, g, b));
    NP3.setPixelColor(0, NP3.Color(r, g, b));
    NP1.show();
    NP3.show();
  }
  else if (curr_drain == 11) {
    NP2.setPixelColor(0, NP2.Color(r, g, b));
    NP2.show();
  }
  else {
    NP1.setPixelColor(0, NP1.Color(r, g, b));
    NP1.show();
  }
}
