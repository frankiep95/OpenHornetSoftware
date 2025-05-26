
// #include "OpenHornetGauge.h"
// #include <SwitecX25.h>

// standard X25.168 range 315 degrees at 1/3 degree steps
#define STEPS (360 * 3)

// bool homed = false;
// int homePos = 0;

// For motors connected to digital pins 4,5,6,7
// SwitecX25 motor1(STEPS, 20, 21, 2, 19);
int coil1 = 21;
int coil2 = 20;
int coil3 = 2;
int coil4 = 19;

byte drivePattern[] = { 0B1010, 0B1000, 0B0001, 0B0101, 0B0100, 0B0010 };
int driveCount = 6;
int driveStep = 0;
int pins[] = { coil1, coil2, coil3, coil4 };
unsigned int position = 0;
int motorSpeed = 2000;

unsigned int targetPos = 0;
bool commandComplete = true;
unsigned int offset = 1000;

// OpenHornetGauge cabinPressure(coil1,coil2,coil3,coil4,3,1000);

void setup(void) {
  pinMode(3, INPUT);
  digitalWrite(3, HIGH);

  for (int a = 0; a < 4; a++) {
    pinMode(pins[a], OUTPUT);
  }

  Serial.begin(9600);
  while (!Serial) {};




  home();
  Serial.print("Enter a step position from 0 through ");
  Serial.print(STEPS - 1);
  Serial.println(".");

  // command(40000);
}

void drive() {
  byte mask = drivePattern[driveStep];
  for (int i = 0; i < 4; i++) {
    digitalWrite(pins[i], mask & 0x1);
    mask >>= 1;
    delayMicroseconds(motorSpeed);
  }
}

void decrement() {
  driveStep = (driveStep + 1) % driveCount;
  position--;
  drive();
}

void increment() {
  driveStep = (driveStep + 5) % driveCount;
  position++;
  drive();
}

void command(unsigned int value) {
    static int nextPos = 0;
      char c = value;
    if (c == 10 || c == 13) {
      targetPos = nextPos;
      nextPos = 0;
    } else if (c >= '0' && c <= '9') {
      nextPos = 10 * nextPos + (c - '0');
    }
  commandComplete = false;
  targetPos = value;
  Serial.println(targetPos);
}

void updatePos() {

  unsigned int a = map(position, 0, STEPS, 0, 65535);


  if (!commandComplete) {

    (targetPos - a) > (a - targetPos) ? decrement() : increment();

    if (abs(a - targetPos) < 100 && !commandComplete) {
      commandComplete = true;
      Serial.print("command Complete");
    }
  }
}

void loop(void) {
  static int nextPos = 0;
  // the motor only moves when you call update
 updatePos();
  
  if (Serial.available()) {
    char c = Serial.read();
    if (c==10 || c==13) {
command(nextPos);
      nextPos = 0;
    } else if (c>='0' && c<='9') {
      nextPos = 10*nextPos + (c-'0');
    }
  }
}

void home() {
  Serial.println("Homing...");
  while (digitalRead(3) == HIGH) {
    decrement();
  }
  if (digitalRead(3) == LOW) {
    for (int a = 0; a < 100; a++) {
      increment();
    }
  }
  while (digitalRead(3) == HIGH) {
    decrement();
    delay(20);
  }

  command(offset);
  position = 0;
  Serial.println("Homing complete");
}
