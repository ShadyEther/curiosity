#include <AFMotor.h>
#include <NewPing.h>
#include <NewTone.h>


#define TRIG_PIN A4
#define ECHO_PIN A5

#define BUZZER 10
#define LED 9

#define MAX_DISTANCE 200
#define MAX_SPEED 215  // Sets speed of DC motors
#define MAX_SPEED_OFFSET 50

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

AF_DCMotor motor1(1);  // First motor to connection 1
AF_DCMotor motor2(2);  // First motor to connection 1

boolean goesForward = false;

int distance = 100;
int speedSet = 0;

int duration = 150;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
}

void loop() {
  delay(40);
  distance = readPing();
  if (distance <= 10) {
    moveStop();
    soundHorn(duration - (duration * 0.75));
    delay(100);
  } 
  else if (distance <= 20) {
    soundHorn(duration - (duration * 0.5));
    moveForward();
    delay(100);
  } 
  else if (distance <= 40) {
    soundHorn(duration);
    moveForward();
    delay(100);
  } 
  else {
    moveForward();
  }
}


int readPing() {
  delay(5);
  int cm = sonar.ping_cm();
  if (cm == 0) {
    cm = 250;
  }
  return cm;
}

void moveStop() {
  for (speedSet = MAX_SPEED; speedSet > 0; speedSet -= MAX_SPEED_OFFSET) {
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet);
    delay(5);
  }
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  goesForward = false;
}

void moveForward() {
  if (goesForward == false) {
    goesForward = true;
    motor1.setSpeed(0);
    motor2.setSpeed(0);
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    // Slowly bring up speed to avoid loading down
    // batteries too quickly
    for (speedSet = 0; speedSet < MAX_SPEED; speedSet += MAX_SPEED_OFFSET) {
      motor1.setSpeed(speedSet);
      motor2.setSpeed(speedSet);
      delay(5);
    }
  }
}


void soundHorn(int duration) {
  NewTone(BUZZER, 1000);
  digitalWrite(LED, HIGH);
  delay(duration);
  noNewTone(BUZZER);
  digitalWrite(LED, LOW);
  delay(duration);
}

