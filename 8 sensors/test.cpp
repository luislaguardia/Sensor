// notes
// for testing

// Motor control pins
int mot1 = 9;
int mot2 = 6;
int mot3 = 5;
int mot4 = 3;

// Sensor pins (Assuming sensors are connected to digital pins 2 to 9)
int sensors[8] = {2, 3, 4, 5, 6, 7, 8, 9};
int sensorValues[8];

// Calibration values
int threshold = 500; // Threshold to determine if a sensor detects the line

void setup() {
  // Initialize motor pins as outputs
  pinMode(mot1, OUTPUT);
  pinMode(mot2, OUTPUT);
  pinMode(mot3, OUTPUT);
  pinMode(mot4, OUTPUT);

  // Initialize sensor pins as inputs
  for (int i = 0; i < 8; i++) {
    pinMode(sensors[i], INPUT);
  }

  Serial.begin(9600); // For debugging
}

void loop() {
  // Read all 8 sensors
  for (int i = 0; i < 8; i++) {
    sensorValues[i] = digitalRead(sensors[i]);
  }

  // Calculate position based on sensor values
  int position = calculatePosition();

  // Control motors based on the position
  if (position < -2) {
    // Turn left
    turnLeft();
  } else if (position > 2) {
    // Turn right
    turnRight();
  } else {
    // Move forward
    moveForward();
  }
}

// Calculate line position based on sensor values
int calculatePosition() {
  int weightedSum = 0;
  int activeSensors = 0;

  // Calculate the weighted sum of active sensors
  for (int i = 0; i < 8; i++) {
    if (sensorValues[i] == 1) {
      weightedSum += (i - 3.5) * 10; // Weighted by position
      activeSensors++;
    }
  }

  // Return the average position
  if (activeSensors > 0) {
    return weightedSum / activeSensors;
  } else {
    // No line detected, return an out-of-bounds position
    return 0;
  }
}

void moveForward() {
  analogWrite(mot1, 255); // Left motor forward
  analogWrite(mot2, 0);
  analogWrite(mot3, 255); // Right motor forward
  analogWrite(mot4, 0);
}

void turnLeft() {
  analogWrite(mot1, 150); // Slow down left motor
  analogWrite(mot2, 0);
  analogWrite(mot3, 255); // Right motor full speed
  analogWrite(mot4, 0);
}

void turnRight() {
  analogWrite(mot1, 255); // Left motor full speed
  analogWrite(mot2, 0);
  analogWrite(mot3, 150); // Slow down right motor
  analogWrite(mot4, 0);
}
