#include <Adafruit_NeoPixel.h>

// Define water sensor pins
#define PIN_WATER_READ A0
#define PIN_WATER_POWER 3

// Define neopixel pins
#define PIN_NEOPIXEL 2

// Define animation constants
#define NUM_PIXELS 4
#define THRESHOLD 25
#define DEFAULT_GLOW 5
#define DEFAULT_FLASH 0
#define DEFAULT_DRAIN 0
#define GLOW_INCREMENT 25
#define FLASH_INCREMENT 1
#define DRAIN_INCREMENT 1

Adafruit_NeoPixel NP(NUM_PIXELS, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);

// Determine if animation is played
int prev_value = 0;

// For glow animation
int curr_glow = DEFAULT_GLOW;
int increase_glow = 0;

// For flash animation
int curr_flash = DEFAULT_FLASH;

// For drain animation
int curr_drain = DEFAULT_DRAIN;

void setup() {
  pinMode(PIN_WATER_READ, INPUT);
  pinMode(PIN_WATER_POWER, OUTPUT);
  digitalWrite(PIN_WATER_POWER, LOW);
  NP.begin();
  Serial.begin(9600);
}

void loop() {
  NP.clear();
  NP.show();
  // Read the water sensor value
  int curr_value = readSensor();
  // For debugging
  Serial.print("loop() prev ");
  Serial.print(prev_value);
  Serial.print(" curr ");
  Serial.println(curr_value);
  // Check if the value has decreased
  if (prev_value - curr_value >= THRESHOLD) {
    curr_glow = DEFAULT_GLOW;
    curr_flash = DEFAULT_FLASH;
    drain(255, 255, 255);
  }
  // Check if the value has increased
  else if (curr_value - prev_value >= THRESHOLD) {
    curr_drain = DEFAULT_DRAIN;
    glow(0, 0, 255);
    //flash(255, 255, 255);
  }
  // Check if the drain animation is still supposed to be playing
  else if (curr_drain > DEFAULT_DRAIN)
    drain(255, 255, 255);
  // Check if the glow animation is still supposed to be playing
  else if (curr_glow > DEFAULT_GLOW)
    glow(0, 0, 255);
  // Check if the flash animation is still supposed to be playing
  /*else if (curr_flash > DEFAULT_FLASH)
    flash(255, 255, 255);*/
  prev_value = curr_value;
  // Delay till the next iteration
  delay(100);
}

int readSensor() {
  digitalWrite(PIN_WATER_POWER, HIGH);
  delay(10);
  int val = analogRead(PIN_WATER_READ);
  digitalWrite(PIN_WATER_POWER, LOW);
  return val;
}

void glow(int r, int g, int b) {
  //Serial.println("glowing"); // For debugging
  curr_glow += pow(-1, increase_glow) * GLOW_INCREMENT;
  for (int pixel = 0; pixel < NUM_PIXELS; pixel++)
    NP.setPixelColor(pixel, NP.Color(r * curr_glow / 255, g * curr_glow / 255, b * curr_glow / 255));
  NP.show();
  if (curr_glow == DEFAULT_GLOW || curr_glow == 255)
    increase_glow = 1 - increase_glow;
}

void flash(int r, int g, int b) {
  //Serial.println("flashing"); // For debugging
  curr_flash = (curr_flash + FLASH_INCREMENT) % NUM_PIXELS;
  NP.setPixelColor(curr_flash, NP.Color(r, g, b));
  NP.show();
}

void drain(int r, int g, int b) {
  //Serial.println("draining"); // For debugging
  curr_drain = (curr_drain - DRAIN_INCREMENT) % NUM_PIXELS;
  NP.setPixelColor(curr_drain, NP.Color(r, g, b));
  NP.show();
}
