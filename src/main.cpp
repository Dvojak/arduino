#include <Arduino.h>

int R_PIN = 6; // Pin for the red portion of the LED
int G_PIN = 5; // Pin for the green portion of the LED
int B_PIN = 4; // Pin for the blue portion of the LED
int JX_PIN = A0; // Pin for the Joystick X Direction (Analog)
int JY_PIN = A1; // Pin for the Joystick Y Direction (Analog)

int joyX; // Variable to store the Joystick X reading
int joyY; // Variable to store the Joystick Y reading

// Setup the Arduino
void setup() 
{
  pinMode(R_PIN, OUTPUT); // Set pin for red LED as output
  pinMode(G_PIN, OUTPUT); // Set pin for green LED as output
  pinMode(B_PIN, OUTPUT); // Set pin for blue LED as output
}

// This function will update the RGB LED when called
void setRGB(int rLed, int gLed, int bLed)
{
  analogWrite(R_PIN, rLed);
  analogWrite(G_PIN, gLed);
  analogWrite(B_PIN, bLed);
}

// This code will run infinitely
void loop() 
{
  delay(100); // Delay 100ms to slow to 10 readings per second
  joyX = analogRead(JX_PIN); // Read the X position
  joyY = analogRead(JY_PIN); // Read the Y position

  // Define threshold and center value
  int centerValue = 512; // Center value for joystick
  int threshold = 10; // You can adjust this value

  // Initialize RGB values
  int rValue = 0;
  int gValue = 0;
  int bValue = 0;

  // Calculate the distance from the center
  int xDist = abs(joyX - centerValue);
  int yDist = abs(joyY - centerValue);

  // Map the distance to brightness (1-255)
  if (xDist > threshold) {
    int brightnessX = map(xDist, threshold, 512, 1, 255); // Map only when past the threshold
    if (joyX < centerValue) {
      bValue = brightnessX; // Left: Blue
    } else {
      gValue = brightnessX; // Right: Green
    }
  }

  if (yDist > threshold) {
    int brightnessY = map(yDist, threshold, 512, 1, 255); // Map only when past the threshold
    if (joyY > centerValue) {
      rValue = brightnessY; // Down: Red
    }
  }

  // Set the RGB LED
  setRGB(rValue, gValue, bValue);
}
