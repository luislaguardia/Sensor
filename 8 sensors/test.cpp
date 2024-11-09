// new (need notes)
// for testing

int mot1 = 9;
int mot2 = 6;
int mot3 = 5;
int mot4 = 3;

int sensors[8] = {2, 3, 4, 5, 6, 7, 8, 9};
int sensorValues[8];

int threshold = 500;

void setup() {
  pinMode(mot1, OUTPUT);
  pinMode(mot2, OUTPUT);
  pinMode(mot3, OUTPUT);
  pinMode(mot4, OUTPUT);

  for (int i = 0; i < 8; i++) {
    pinMode(sensors[i], INPUT);
  }

  Serial.begin(9600);
}

void loop() {
  for (int i = 0; i < 8; i++) {
    sensorValues[i] = digitalRead(sensors[i]);
  }

  int position = calculatePosition();

  if (position < -2) {
    turnLeft();
  } else if (position > 2) {
    turnRight();
  } else {
    moveForward();
  }
}

int calculatePosition() {
  int weightedSum = 0;
  int activeSensors = 0;

  for (int i = 0; i < 8; i++) {
    if (sensorValues[i] == 1) {
      weightedSum += (i - 3.5) * 10;
      activeSensors++;
    }
  }

  if (activeSensors > 0) {
    return weightedSum / activeSensors;
  } else {
    return 0;
  }
}

void moveForward() {
  analogWrite(mot1, 255);
  analogWrite(mot2, 0);
  analogWrite(mot3, 255);
  analogWrite(mot4, 0);
}

void turnLeft() {
  analogWrite(mot1, 150);
  analogWrite(mot2, 0);
  analogWrite(mot3, 255);
  analogWrite(mot4, 0);
}

void turnRight() {
  analogWrite(mot1, 255);
  analogWrite(mot2, 0);
  analogWrite(mot3, 150);
  analogWrite(mot4, 0);
}
