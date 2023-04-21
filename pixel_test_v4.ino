#include <Adafruit_NeoPixel.h>

// Define water sensor pins
#define PIN_WATER_READ_1 A0
#define PIN_WATER_READ_2 A1
#define PIN_WATER_READ_3 A2
#define PIN_WATER_READ_4 A3
#define PIN_WATER_READ_5 A4
#define PIN_WATER_READ_6 A5
#define PIN_WATER_POWER_1 8
#define PIN_WATER_POWER_2 9
#define PIN_WATER_POWER_3 10
#define PIN_WATER_POWER_4 11
#define PIN_WATER_POWER_5 12
#define PIN_WATER_POWER_6 13

// Define neopixel pins
#define PIN_NEOPIXEL_1 2
#define PIN_NEOPIXEL_2 3
#define PIN_NEOPIXEL_3 4
#define PIN_NEOPIXEL_4 5
#define PIN_NEOPIXEL_5 6
#define PIN_NEOPIXEL_6 7

// Define push button pins
#define PIN_DAY_NIGHT 14
#define PIN_GRENADE 15
#define PIN_MIST 16
#define PIN_STREAM 17

// Define animation constants
#define NUM_PIXELS 4
#define THRESHOLD 3
#define DEFAULT_FLASH 0
#define DEFAULT_DRAIN 0
#define GLOW_INCREMENT 25
#define FLASH_INCREMENT 1
#define RIPPLE_INCREMENT 25
#define DRAIN_INCREMENT 1
#define RIPPLE_THRESHOLD 50

Adafruit_NeoPixel NP1(NUM_PIXELS, PIN_NEOPIXEL_1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel NP2(NUM_PIXELS, PIN_NEOPIXEL_2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel NP3(NUM_PIXELS, PIN_NEOPIXEL_3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel NP4(NUM_PIXELS, PIN_NEOPIXEL_4, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel NP5(NUM_PIXELS, PIN_NEOPIXEL_5, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel NP6(NUM_PIXELS, PIN_NEOPIXEL_6, NEO_GRB + NEO_KHZ800);

// Determine animation type
int animation_type = 2;

// Determine if animation is played
float prev_value_1 = 0;
float prev_value_2 = 0;
float prev_value_3 = 0;
float prev_value_4 = 0;
float prev_value_5 = 0;
float prev_value_6 = 0;
bool prev_anim_1 = false;
bool prev_anim_2 = false;
bool prev_anim_3 = false;
bool prev_anim_4 = false;
bool prev_anim_5 = false;
bool prev_anim_6 = false;

// For glow animation
int default_glow = 5;
int curr_glow_1 = default_glow;
int increase_glow_1 = 0;
int curr_glow_2 = default_glow;
int increase_glow_2 = 0;
int curr_glow_3 = default_glow;
int increase_glow_3 = 0;
int curr_glow_4 = default_glow;
int increase_glow_4 = 0;
int curr_glow_5 = default_glow;
int increase_glow_5 = 0;
int curr_glow_6 = default_glow;
int increase_glow_6 = 0;

// For flash animation
int curr_flash_1 = DEFAULT_FLASH;
int curr_flash_2 = DEFAULT_FLASH;
int curr_flash_3 = DEFAULT_FLASH;
int curr_flash_4 = DEFAULT_FLASH;
int curr_flash_5 = DEFAULT_FLASH;
int curr_flash_6 = DEFAULT_FLASH;

// For ripple animation
int default_ripple = 0;
int curr_ripple_1 = default_ripple;
int curr_ripple_2 = default_ripple;
int curr_ripple_3 = default_ripple;
int curr_ripple_4 = default_ripple;
int curr_ripple_5 = default_ripple;
int curr_ripple_6 = default_ripple;

// For drain animation
int curr_drain_1 = DEFAULT_DRAIN;
int curr_drain_2 = DEFAULT_DRAIN;
int curr_drain_3 = DEFAULT_DRAIN;
int curr_drain_4 = DEFAULT_DRAIN;
int curr_drain_5 = DEFAULT_DRAIN;
int curr_drain_6 = DEFAULT_DRAIN;

void setup() {
  // Set up water sensors
  pinMode(PIN_WATER_READ_1, INPUT);
  pinMode(PIN_WATER_POWER_1, OUTPUT);
  digitalWrite(PIN_WATER_POWER_1, LOW);
  pinMode(PIN_WATER_READ_2, INPUT);
  pinMode(PIN_WATER_POWER_2, OUTPUT);
  digitalWrite(PIN_WATER_POWER_2, LOW);
  pinMode(PIN_WATER_READ_3, INPUT);
  pinMode(PIN_WATER_POWER_3, OUTPUT);
  digitalWrite(PIN_WATER_POWER_3, LOW);
  pinMode(PIN_WATER_READ_4, INPUT);
  pinMode(PIN_WATER_POWER_4, OUTPUT);
  digitalWrite(PIN_WATER_POWER_4, LOW);
  pinMode(PIN_WATER_READ_5, INPUT);
  pinMode(PIN_WATER_POWER_5, OUTPUT);
  digitalWrite(PIN_WATER_POWER_5, LOW);
  pinMode(PIN_WATER_READ_6, INPUT);
  pinMode(PIN_WATER_POWER_6, OUTPUT);
  digitalWrite(PIN_WATER_POWER_6, LOW);
  // Set up buttons
  pinMode(PIN_DAY_NIGHT, INPUT_PULLUP);
  pinMode(PIN_GRENADE, INPUT_PULLUP);
  pinMode(PIN_MIST, INPUT_PULLUP);
  pinMode(PIN_STREAM, INPUT_PULLUP);
  // Set up neopixel strips
  NP1.begin();
  NP2.begin();
  NP3.begin();
  NP4.begin();
  NP5.begin();
  NP6.begin();
  // For debugging
  Serial.begin(9600);
}

void loop() {
  // Read the button and sensor values
  checkDayNight();
  checkAnimationType();
  // Check on each flower
  checkFlower(PIN_WATER_POWER_1, PIN_WATER_READ_1, NP1, prev_value_1, prev_anim_1, curr_glow_1, increase_glow_1, curr_flash_1, curr_ripple_1, curr_drain_1);
  checkFlower(PIN_WATER_POWER_2, PIN_WATER_READ_2, NP2, prev_value_2, prev_anim_2, curr_glow_2, increase_glow_2, curr_flash_2, curr_ripple_2, curr_drain_2);
  checkFlower(PIN_WATER_POWER_3, PIN_WATER_READ_3, NP3, prev_value_3, prev_anim_3, curr_glow_3, increase_glow_3, curr_flash_3, curr_ripple_3, curr_drain_3);
  checkFlower(PIN_WATER_POWER_4, PIN_WATER_READ_4, NP4, prev_value_4, prev_anim_4, curr_glow_4, increase_glow_4, curr_flash_4, curr_ripple_4, curr_drain_4);
  checkFlower(PIN_WATER_POWER_5, PIN_WATER_READ_5, NP5, prev_value_5, prev_anim_5, curr_glow_5, increase_glow_5, curr_flash_5, curr_ripple_5, curr_drain_5);
  checkFlower(PIN_WATER_POWER_6, PIN_WATER_READ_6, NP6, prev_value_6, prev_anim_6, curr_glow_6, increase_glow_6, curr_flash_6, curr_ripple_6, curr_drain_6);
  // Delay till the next iteration
  delay(100);
}

float checkWater(int difference) {
  // From water sensor calibration graph
  float result = exp((float(difference) - 172.27) / 88.491);
  // For debugging
  /*Serial.print("checkWater() difference ");
  Serial.print(difference);
  Serial.print(" result ");
  Serial.println(result);*/
  return result;
}

void checkDayNight() {
  int state = digitalRead(PIN_DAY_NIGHT);
  if (state == LOW) {
    // Reverse glow animation values
    default_glow = 255 - default_glow;
    curr_glow_1 = 255 - curr_glow_1;
    curr_glow_2 = 255 - curr_glow_2;
    curr_glow_3 = 255 - curr_glow_3;
    curr_glow_4 = 255 - curr_glow_4;
    curr_glow_5 = 255 - curr_glow_5;
    curr_glow_6 = 255 - curr_glow_6;
    increase_glow_1 = 1 - increase_glow_1;
    increase_glow_2 = 1 - increase_glow_2;
    increase_glow_3 = 1 - increase_glow_3;
    increase_glow_4 = 1 - increase_glow_4;
    increase_glow_5 = 1 - increase_glow_5;
    increase_glow_6 = 1 - increase_glow_6;
    // Reverse ripple animation values
    default_ripple = 255 - default_ripple;
    curr_ripple_1 = 255 - curr_ripple_1;
    curr_ripple_2 = 255 - curr_ripple_2;
    curr_ripple_3 = 255 - curr_ripple_3;
    curr_ripple_4 = 255 - curr_ripple_4;
    curr_ripple_5 = 255 - curr_ripple_5;
    curr_ripple_6 = 255 - curr_ripple_6;
    // Set all to previously animating
    prev_anim_1 = true;
    prev_anim_2 = true;
    prev_anim_3 = true;
    prev_anim_4 = true;
    prev_anim_5 = true;
    prev_anim_6 = true;
    // For debugging
    Serial.print("checkDayNight() changing from ");
    Serial.print(default_glow == 250 ? "day" : "night");
    Serial.print(" to ");
    Serial.println(default_glow == 250 ? "night" : "day");
  }
}

int checkAnimationType() {
  int grenade_state = digitalRead(PIN_GRENADE);
  int mist_state = digitalRead(PIN_MIST);
  int stream_state = digitalRead(PIN_STREAM);
  // Change the animation type if any of the buttons are pressed
  bool prev_anim = false;
  if (grenade_state == LOW) {
    prev_anim = animation_type != 0;
    animation_type = 0;
  }
  else if (mist_state == LOW) {
    prev_anim = animation_type != 1;
    animation_type = 1;
  }
  else if (stream_state == LOW) {
    prev_anim = animation_type != 2;
    animation_type = 2;
  }
  else
    return;
  if (prev_anim) {
    // Set all to previously animating
    prev_anim_1 = true;
    prev_anim_2 = true;
    prev_anim_3 = true;
    prev_anim_4 = true;
    prev_anim_5 = true;
    prev_anim_6 = true;
  }
  // For debugging
  Serial.print("checkAnimationType() changing animation type to ");
  Serial.println(animation_type == 0 ? "grenade" : animation_type == 1 ? "mist" : "stream");
}

void checkFlower(int pin_water_power, int pin_water_read, Adafruit_NeoPixel &np, float &prev_value, bool &prev_anim, int &curr_glow, int &increase_glow, int &curr_flash, int &curr_ripple, int &curr_drain) {
  // Read the water sensor value
  int sensor_value = readSensor(pin_water_power, pin_water_read);
  float curr_value = checkWater(sensor_value);
  int max_ripple = default_ripple + pow(-1, int(default_ripple == 255)) * 250;
  // For debugging
  /*Serial.print("checkFlower() prev ");
  Serial.print(prev_value);
  Serial.print(" curr ");
  Serial.println(curr_value);*/
  // Check if the value has decreased
  if (prev_value - curr_value >= THRESHOLD) {
    prev_anim = true;
    curr_glow = default_glow;
    curr_flash = DEFAULT_FLASH;
    curr_ripple = default_ripple;
    drain(np, curr_drain, 255, 255, 255);
  }
  // Check if the value has increased
  else if (curr_value - prev_value >= THRESHOLD) {
    prev_anim = true;
    curr_drain = DEFAULT_DRAIN;
    if (animation_type == 0)
      ripple(np, curr_ripple, max_ripple, 255, 0, 0);
    else if (animation_type == 1)
      glow(np, curr_glow, increase_glow, 0, 0, 255);
    else  // animation_type == 2
      flash(np, curr_flash, 255, 255, 255);
  }
  // Check if the drain animation is still supposed to be playing
  else if (curr_drain > DEFAULT_DRAIN) {
    prev_anim = true;
    drain(np, curr_drain, 255, 255, 255);
  }
  else if (animation_type == 0 && (curr_ripple_1 != default_ripple || curr_ripple_2 != default_ripple || curr_ripple_3 != default_ripple || curr_ripple_4 != default_ripple || curr_ripple_5 != default_ripple || curr_ripple_6 != default_ripple)) {
    int threshold_ripple = max_ripple + pow(-1, int(default_ripple == 0)) * RIPPLE_THRESHOLD;
    // Check if the flower should start a ripple animation from another flower
    if ((pin_water_power == PIN_WATER_POWER_1 && curr_ripple_1 == default_ripple && (curr_ripple_2 == threshold_ripple || curr_ripple_3 == threshold_ripple)) ||
        (pin_water_power == PIN_WATER_POWER_2 && curr_ripple_2 == default_ripple && (curr_ripple_1 == threshold_ripple || curr_ripple_3 == threshold_ripple || curr_ripple_4 == threshold_ripple || curr_ripple_5 == threshold_ripple)) ||
        (pin_water_power == PIN_WATER_POWER_3 && curr_ripple_3 == default_ripple && (curr_ripple_1 == threshold_ripple || curr_ripple_2 == threshold_ripple || curr_ripple_5 == threshold_ripple || curr_ripple_6 == threshold_ripple)) ||
        (pin_water_power == PIN_WATER_POWER_4 && curr_ripple_4 == default_ripple && (curr_ripple_2 == threshold_ripple || curr_ripple_5 == threshold_ripple)) ||
        (pin_water_power == PIN_WATER_POWER_5 && curr_ripple_5 == default_ripple && (curr_ripple_2 == threshold_ripple || curr_ripple_3 == threshold_ripple || curr_ripple_4 == threshold_ripple || curr_ripple_6 == threshold_ripple)) ||
        (pin_water_power == PIN_WATER_POWER_6 && curr_ripple_6 == default_ripple && (curr_ripple_3 == threshold_ripple || curr_ripple_5 == threshold_ripple))) {
      prev_anim = true;
      ripple(np, curr_ripple, max_ripple, 255, 0, 0);
    }
    // Check if the ripple animation is still supposed to be playing
    else if (curr_ripple != default_ripple) {
      prev_anim = true;
      ripple(np, curr_ripple, curr_ripple + pow(-1, int(default_ripple == 0)) * RIPPLE_INCREMENT, 255, 0, 0);
    }
  }
  // Check if the glow animation is still supposed to be playing
  else if (animation_type == 1 && curr_glow != default_glow) {
    prev_anim = true;
    glow(np, curr_glow, increase_glow, 0, 0, 255);
  }
  // Check if the flash animation is still supposed to be playing
  else if (animation_type == 2 && curr_flash > DEFAULT_FLASH) {
    prev_anim = true;
    flash(np, curr_flash, 255, 255, 255);
  }
  // Refresh light display to default state if previously animating
  else if (prev_anim) {
    prev_anim = false;
    // Day mode - off by default; night mode - on by default
    if (default_glow == 250 || default_ripple == 255) {
      for (int pixel = 0; pixel < NUM_PIXELS; pixel++)
        np.setPixelColor(pixel, animation_type == 0 ? np.Color(255, 0, 0) : animation_type == 1 ? np.Color(0, 0, 255) : np.Color(0, 255, 0));
    }
    else
      np.clear();
    np.show();
  }
  prev_value = curr_value;
}

int readSensor(int pin_water_power, int pin_water_read) {
  digitalWrite(pin_water_power, HIGH);
  delay(10);
  int val = analogRead(pin_water_read);
  digitalWrite(pin_water_power, LOW);
  return val;
}

void glow(Adafruit_NeoPixel &np, int &curr_glow, int &increase_glow, int r, int g, int b) {
  //Serial.println("glowing"); // For debugging
  np.clear();
  curr_glow += pow(-1, increase_glow) * GLOW_INCREMENT;
  for (int pixel = 0; pixel < NUM_PIXELS; pixel++)
    np.setPixelColor(pixel, np.Color(r * curr_glow / 255, g * curr_glow / 255, b * curr_glow / 255));
  np.show();
  if (curr_glow == default_glow || curr_glow == 250 + pow(-1, int(default_glow == 250)) * default_glow)
    increase_glow = 1 - increase_glow;
}

void flash(Adafruit_NeoPixel &np, int &curr_flash, int r, int g, int b) {
  //Serial.println("flashing"); // For debugging
  np.clear();
  curr_flash = (curr_flash + FLASH_INCREMENT) % NUM_PIXELS;
  if (default_glow == 5)
    np.setPixelColor(curr_flash, np.Color(r, g, b));
  else {
    for (int pixel = 0; pixel < NUM_PIXELS; pixel++) {
      if (pixel == curr_flash)
        continue;
      np.setPixelColor(pixel, np.Color(r, g, b));
    }
  }
  np.show();
}

void ripple(Adafruit_NeoPixel &np, int &curr_ripple, int new_ripple, int r, int g, int b) {
  //Serial.println("rippling");  // For debugging
  np.clear();
  curr_ripple = new_ripple;
  for (int pixel = 0; pixel < NUM_PIXELS; pixel++)
    np.setPixelColor(pixel, np.Color(r * curr_ripple / 255, g * curr_ripple / 255, b * curr_ripple / 255));
  np.show();
}

void drain(Adafruit_NeoPixel &np, int &curr_drain, int r, int g, int b) {
  //Serial.println("draining"); // For debugging
  np.clear();
  curr_drain -= DRAIN_INCREMENT;
  if (curr_drain < 0)
    curr_drain += NUM_PIXELS;
  if (default_glow == 5)
    np.setPixelColor(curr_drain, np.Color(r, g, b));
  else {
    for (int pixel = 0; pixel < NUM_PIXELS; pixel++) {
      if (pixel == curr_drain)
        continue;
      np.setPixelColor(pixel, np.Color(r, g, b));
    }
  }
  np.show();
}
