#include <QTRSensors.h>

// Motor control pins
int mot1 = 9; // Left motor forward
int mot2 = 6; // Left motor backward
int mot3 = 5; // Right motor forward
int mot4 = 3; // Right motor backward

// Sensor array configuration
#define NUM_SENSORS 8
#define TIMEOUT 2500
#define EMITTER_PIN 2

QTRSensorsAnalog qtra((unsigned char[]) {A0, A1, A2, A3, A4, A5, A6, A7}, NUM_SENSORS, TIMEOUT, EMITTER_PIN);
unsigned int sensorValues[NUM_SENSORS];

// Motor speed
int baseSpeed = 200; // Base motor speed
int maxSpeed = 255;  // Max PWM speed for motors

void setup() {
  // Initialize motor pins as outputs
  pinMode(mot1, OUTPUT);
  pinMode(mot2, OUTPUT);
  pinMode(mot3, OUTPUT);
  pinMode(mot4, OUTPUT);

  Serial.begin(9600);
  delay(1000); // Wait for startup

  // Calibrate sensors
  for (int i = 0; i < 400; i++) {
    qtra.calibrate();
    delay(20);
  }
}

void loop() {
  // Read the sensor array and calculate the line position
  int position = qtra.readLine(sensorValues);

  // Calculate error based on the center position (3500)
  int error = position - 3500;

  // Proportional control for direction
  int turnSpeed = error / 20;

  // Set motor speeds
  int leftSpeed = baseSpeed + turnSpeed;
  int rightSpeed = baseSpeed - turnSpeed;

  // Constrain speeds to prevent overflow
  leftSpeed = constrain(leftSpeed, 0, maxSpeed);
  rightSpeed = constrain(rightSpeed, 0, maxSpeed);

  // Control motors
  analogWrite(mot1, leftSpeed);
  analogWrite(mot2, 0);         // Left motor forward
  analogWrite(mot3, rightSpeed);
  analogWrite(mot4, 0);         // Right motor forward

  delay(10); // Small delay for stability
}