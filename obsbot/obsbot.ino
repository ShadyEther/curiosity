#include <AFMotor.h>
#include <NewPing.h>

#define TRIG_PIN A4
#define ECHO_PIN A5

#define MAX_DISTANCE 200
#define MAX_SPEED 190  // Sets speed of DC motors
#define MAX_SPEED_OFFSET 20

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

AF_DCMotor motor1(1, MOTOR12_1KHZ);  // First motor to connection 1
AF_DCMotor motor2(3, MOTOR12_1KHZ);  // Second motor to connection 3

boolean goesForward = false;

int distance = 100;  // Define an int for distance and speed
int speedSet = 0;

void setup() {
}

void loop() {
  int distanceR = 0;
  int distanceL = 0;
  delay(40);


  if (distance <= 15) {
    moveStop();
    delay(100);

    moveBackward();
    delay(300);

    moveStop();
    delay(200);

    distanceR = lookRight();
    delay(200);

    distanceL = lookLeft();
    delay(200);

    if (distanceR >= distanceL) {
      turnRight();
      moveStop();

    } 

    else {  // Or else carry on
      turnLeft();
      moveStop();

    }
  } 
  else {
    moveForward();
  }

  distance = readPing();

}

int lookRight() {  // The servo looks to the right
  myservo.write(50);//rotate to right
  delay(500);

  int distance = readPing();
  delay(100);

  myservo.write(115);//rotate to original
  return distance;
}

int lookLeft() {  // The servo looks to the left
  myservo.write(170);//rotate to left
  delay(500);

  int distance = readPing();
  delay(100);

  myservo.write(115);//return to original position
  return distance;
}

int readPing() {
  delay(70);
  int cm = sonar.ping_cm();

  if (cm == 0) {
    cm = 250;
  }

  return cm;
}

void moveStop() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
}

void moveForward() {
  if (!goesForward) {  // If area is clear, motors move forward
    goesForward = true;
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    // Slowly bring up speed to avoid loading down
    // batteries too quickly

    for (speedSet = 0; speedSet < MAX_SPEED; speedSet += 2) {
      motor1.setSpeed(speedSet);
      motor2.setSpeed(speedSet + MAX_SPEED_OFFSET);
      delay(5);
    }
  }
}

void moveBackward() {
  goesForward = false;
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  // Slowly bring up speed to avoid loading down
  // batteries too quickly
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet += 2) {
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet + MAX_SPEED_OFFSET);
    delay(5);
  }
}

void turnRight() {  // Movement for turning right
  motor1.run(FORWARD);
  motor2.run(BACKWARD);
  delay(300);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
}

void turnLeft() {  // Movement for turning left
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
  delay(300);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
}
