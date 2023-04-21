int switchPin = 2; // Define the pin for the switch
int laserPin = 13; // Define the pin for the laser module

void setup() {
  pinMode(laserPin, OUTPUT); // Set pin 13 as output for the laser module
  pinMode(switchPin, INPUT_PULLUP); // Set pin 2 as input with internal pull-up resistor
}

void loop() {
  digitalWrite(laserPin, digitalRead(switchPin)); // Turn on the laser module
  delay(100);
}
